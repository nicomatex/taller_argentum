#ifndef ITEM_CONTAINER_H
#define ITEM_CONTAINER_H

#include <array>
#include <vector>

#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"
#include "item.h"
#include "gold.h"

// Segun mock el inventario tiene 12 slots -> el oro no ocupa un slot
// en el inventario.

#define INV_SIZE 12

class FullItemContainerException : public std::exception {
   public:
    const char* what() const throw();
};

class EmptySlotException : public std::exception {
   public:
    const char* what() const throw();
};

class OutOfRangeSlotException : public std::exception {
   public:
    const char* what() const throw();
};

typedef struct inventory {
    ItemId items_ids[INV_SIZE];
    uint32_t items_stacks[INV_SIZE];
    unsigned int current_gold;
} inventory_t;

inline void to_json(nlohmann::json& j, const inventory_t& i) {
    j["items_ids"] = i.items_ids;
    j["items_stacks"] = i.items_stacks;
    j["curr_gold"] = i.current_gold;
}

inline void from_json(const nlohmann::json& j, inventory_t& i) {
    j["items_ids"].get_to(i.items_ids);
    j["items_stacks"].get_to(i.items_stacks);
    j["curr_gold"].get_to(i.current_gold);
}

class ItemContainer {
   private:
    Gold *gold;
    std::vector<Item*> item_container;
    std::map<ItemId, SlotId> item_id_to_slot;
    nlohmann::json _get_data(bool need_sprite_id) const;

   public:
    ItemContainer();

    ItemContainer(ItemContainer&& other);
    ItemContainer& operator=(ItemContainer&& other);

    ItemContainer(unsigned int slots_amount);
    /**
     * @brief Se crea un inventario a partir del json.
     * 
     * @param inv_json 
     */
    ItemContainer(const nlohmann::json& inv_json);
    /**
     * @brief Se destruyen los items que quedaron almacenados en el
     * inventario, junto con el oro.
     * 
     */
    ~ItemContainer();
    /**
     * @brief Agrega el item entero (con todo su stack) al inventario.
     * Lo invalida haciendo delete del puntero (en caso de que ya existiese
     * un item de ese tipo en algun slot)
     * Si ya existia ese item en el inventario, se agrega en la posicion
     * existente, en caso contrario, se agrega en el slot de menor orden
     * numerico.
     * Lanza FullItemContainerException en caso de que el inventario este
     * lleno.
     * 
     * @param item 
     */
    void add(Item* item);
    /**
     * @brief Agrega una cierta cantidad (stack) del item, al inventario.
     * Lo invalida haciendo delete del puntero (en caso de que ya existiese
     * un item de ese tipo en algun slot, y stack es >= al stack actual del
     * item a depositar)
     * Si ya existia ese item en el inventario, se agrega en la posicion
     * existente, en caso contrario, se agrega en el slot de menor orden
     * numerico.
     * Reduce el stack actual del item a depositar en "stack" cantidad.
     * Lanza FullItemContainerException en caso de que el inventario este lleno.
     * 
     * @param item 
     * @param stack 
     */
    void add(Item* item, uint32_t stack);
    /**
     * @brief Remueve en su totalidad el item que se encuentra en el slot_id,
     * devolviendo un puntero a este.
     * Lanza EmptySlotException en caso de que el slot este vacio.
     * 
     * @param slot_id 
     * @return Item* 
     */
    Item* remove(SlotId slot_id);
    /**
     * @brief Remueve "stack" cantidad del actual_stack del item que se encuentra
     * en el slot_id, devolviendo un puntero a este.
     * Lanza EmptySlotException en caso de que el slot este vacio.
     * 
     * @param slot_id 
     * @param stack 
     * @return Item* 
     */
    Item* remove(SlotId slot_id, uint32_t stack);
    /**
     * @brief Remueve todos los items del inventario, devolviendo un vector
     * que los contiene a todos.
     * 
     * @return std::vector<Item*> 
     */
    std::vector<Item*> remove_all();
    /**
     * @brief Devuelve el SlotId asignado/a asignar al item con item_id.
     * Lanza FullContainerException en caso de que no haya slots
     * disponibles.
     * 
     * @param item_id 
     * @return SlotId 
     */
    SlotId get_available_slot(ItemId item_id);
    const Item& get_item(SlotId slot_id) const;
    bool slot_is_free(SlotId slot_id) const;
    bool has_item(ItemId item_id);
    unsigned int get_gold_stack() const;
    /**
     * @brief Agrega la totalidad del stack del oro al inventario,
     * seteando su stack en 0 (no invalida el puntero)
     * 
     * @param gold 
     */
    void add_gold(Gold* gold);
    /**
     * @brief Retira stack cantidad del stack actual del oro pasado por parametro,
     * depositandolo en el inventario (no invalida el puntero).
     * En caso de que stack sea mayor al stack actual del oro pasado por parametro,
     * lo deposita en su totalidad.
     * 
     * @param gold 
     * @param stack 
     */
    void add_gold(Gold* gold, uint32_t stack);
    /**
     * @brief Remueve la totalidad del oro del inventario (setea el stack en 0), devolviendo
     * un nuevo puntero a Gold con ese stack.
     * 
     * @return Gold* 
     */
    Gold* remove_gold();
    /**
     * @brief Remueve stack cantidad del oro del inventario (reduce su cantidad en stack),
     * devolviendo un nuevo puntero a Gold.
     * Si stack supera la cantidad actual de oro en el inventario, lo remueve en su
     * totalidad.
     * 
     * @param stack 
     * @return Gold* 
     */
    Gold* remove_gold(uint32_t stack);
    bool is_in_range(SlotId slotId) const;
    bool has_slots_left() const;

    /**
     * @brief Informacion para persistir el inventario en el personaje.
     * 
     * @return nlohmann::json 
     */
    nlohmann::json get_persist_data() const;
    /**
     * @brief Informacion a enviar al cliente.
     * 
     * @return nlohmann::json 
     */
    nlohmann::json get_data() const;
};

#endif  // ITEM_CONTAINER_H

/*
    Metodologia al agregar (la que es mas complicada):
    Al agregar el item lo hago de la siguiente manera:
    Pregunto si hay slots libres
    a) Si los hay,
        *) A/B
    b) Si no los hay,
        *) A/B

        A/B:
        Me fijo si tengo en algun slot un item con el mismo
        ItemId (para sumarle el stack del item ingresante al que ya esta),
   pero aca hay varios casos:
            *) No hay slots con ese itemId
                a*) Lo agrego al primer slot disponible (numericamente)
                b*) Exception
            *) Hay slot/slots, devuelta en 2 casos:
                **) Un unico slot:
                        Si tiene stack al maximo
                            a*) Lo agrego al primer slot disponible
   (numericamente)
                            b*) Exception
                        Si no tiene el stack al maximo:
                            Le sumo todo lo que pueda al stack del item del
   inv: a*) La diferencia va al primer slot disponible (numericamente) b*)
   La diferencia queda en el "piso"
                **) Varios slots:
                            Si tienen todos stack al maximo
                             a*) Lo agrego al primer slot disponible
   (numericamente)
                             b*) Exception
                            No tienen todos el stack al maximo:
                             Debo ir llenando los slots en orden numerico
   (SlotId): En caso de quedar diferencia. a*) Lo agrego al primer slot
   disponible (numericamente) b*) Diferencia queda en el piso como en el
   anterior.
*/
