#ifndef INVENTORY_H
#define INVENTORY_H

#include <array>

#include "../../include/nlohmann/json.hpp"
#include "item.h"

// Segun mock el inventario tiene 12 slots -> el oro no va en el inventario

#define INV_SIZE 12

class FullInventoryException : public std::exception {
   public:
    const char* what() const throw();
};

typedef uint8_t SlotId;  // 0 - 11

typedef struct inventory {
    ItemId items_ids[INV_SIZE];
    uint32_t items_stacks[INV_SIZE];
} inventory_t;

inline void to_json(nlohmann::json& j, const inventory_t& i) {
    j["items_ids"] = i.items_ids;
    j["items_stacks"] = i.items_stacks;
}

inline void from_json(const nlohmann::json& j, inventory_t& i) {
    j["items_ids"].get_to(i.items_ids);
    j["items_stacks"].get_to(i.items_stacks);
}

class Inventory {
   private:
    std::array<Item*, INV_SIZE> inventory;
    std::map<ItemId, SlotId> item_id_to_slot;
    nlohmann::json _get_data(bool need_sprite_id) const;
   public:
    Inventory();
    Inventory(const nlohmann::json& inv_json);
    ~Inventory();
    void add(Item* item);
    void add(Item* item, uint32_t stack);
    //void add(Item* item, SlotId slot_id);
    Item* remove(SlotId slot_id);
    Item* remove(SlotId slot_id, uint32_t stack);
    SlotId get_available_slot(ItemId item_id);
    Item* get_item(SlotId slot_id) const;
    bool slot_is_free(SlotId slot_id) const;
    bool has_item(ItemId item_id);
    nlohmann::json get_persist_data() const;
    nlohmann::json get_data() const;
};

#endif  // INVENTORY_H

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
        ItemId (para sumarle el stack del item ingresante al que ya esta), pero
        aca hay varios casos:
            *) No hay slots con ese itemId
                a*) Lo agrego al primer slot disponible (numericamente)
                b*) Exception papu
            *) Hay slot/slots, devuelta en 2 casos:
                **) Un unico slot:
                        Si tiene stack al maximo
                            a*) Lo agrego al primer slot disponible
   (numericamente)
                            b*) Exception papu
                        Si no tiene el stack al maximo:
                            Le sumotodo lo que pueda al stack del item del
                            inv:
                             a*) La diferencia va al primer
   slot disponible (numericamente)
                             b*) La diferencia queda en el "piso"
                **) Varios slots:
                            Si tienen todos stack al maximo
                             a*) Lo agrego al primer slot disponible
   (numericamente) 
                             b*) Exception papu
                            No tienen todos el stack al maximo:
                             Debo
   ir llenando los slots en orden numerico (SlotId): En caso de quedar
   diferencia.
                     a*) Lo agrego al primer slot disponible (numericamente)
                    b*) Diferencia queda en el piso como en el anterior.
*/
