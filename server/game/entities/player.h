#ifndef PLAYER_H
#define PLAYER_H
#include <string>

/// \file

#include "../../attribute_manager.h"
#include "../items/item_container.h"
#include "../map.h"
#include "../position.h"
#include "entity.h"

class Player : public Entity {
   private:
    bool alive;
    const int head_id;
    const int body_id;

    ItemContainer inventory;

    Map& map;
    class_type_t class_type;
    race_type_t race_type;

   public:
    /**
     * @brief Construye a un jugador.
     *
     * @param entity_id
     * @param player_info
     * @param map
     */
    Player(EntityId entity_id, nlohmann::json player_info, Map& map);

    /**
     * @brief Obtiene el tipo de la entidad: PLAYER.
     *
     * @return entity_type_t
     */
    entity_type_t get_type() const override;

    /**
     * @brief Obtiene la clase del jugador.
     *
     * @return class_type_t
     */
    class_type_t get_class_type() const;

    /**
     * @brief Obtiene la raza del jugador.
     *
     * @return race_type_t
     */
    race_type_t get_race_type() const;

    void die() override;
    bool is_alive() const override;

    /**
     * @brief Utilizar un item del inventario.
     *
     * @param slot Selecciona el casillero del inventario a utilizar.
     */
    void use(SlotId slot);
    void add_item(Item* item);

    /**
     * @brief Setea el movimiento del jugador.
     *
     * @param action Empieza (START) o detiene (STOP) el movimiento.
     * @param direction Selecciona la dirección del movimiento.
     */
    void set_movement(mov_action_t action, direction_t direction);
    void update(uint64_t delta_t) override;

    /**
     * @brief Define si un jugador podrá o no atacar a otra entidad.
     *
     * @details Un jugador puede atacar al otro si ambos son de nivel mayor al
     * definido por "newbie level" y la diferencia con éste es mayor a "level
     * difference".
     *
     * @param attacked Entidad a la que se pretende atacar.
     * @return true
     * @return false
     */
    bool can_attack(Entity* attacked) const override;

    /**
     * @brief Obtiene los datos de la entidad para enviar al cliente. (caso
     * PLAYER)
     *
     * ```
     * ej:
     * {
     *     "armor_id": 2,
     *     "body_id": 2,
     *     "curr_exp": 93,
     *     "curr_hp": 83,
     *     "curr_level": 16,
     *     "curr_mp": 43,
     *     "direction": 1,
     *     "entity_id": 1,
     *     "head_id": 2,
     *     "helmet_id": 2,
     *     "limit_exp": 16126,
     *     "max_hp": 336,
     *     "max_mp": 256,
     *     "move_speed": 7,
     *     "name": "tai",
     *     "shield_id": 2,
     *     "type_id": 0,
     *     "weapon_id": 3
     * }
     * ```
     *
     * @return nlohmann::json
     */
    nlohmann::json get_data() const override;

    /**
     * @brief Obtiene la información del inventario del jugador.
     *
     * ```
     * ej:
     * {
     *     "curr_gold": 0,
     *     "items": [
     *         { 1er Slot: Una poción de maná
     *             "actual_stack": 1200,
     *             "item_id": 2,
     *             "name": "Pocion de mana",
     *             "potion_info": {
     *                 "health_var": 0,
     *                 "mana_var": 30
     *             },
     *             "type": 3
     *         },
     *         { // 2do Slot: vacío
     *             "type": 0
     *         },
     *         ...
     *         { // 12avo Slot: vacío
     *             "type": 0
     *         }
     *     ]
     * }
     * ```
     *
     * @return nlohmann::json
     */
    nlohmann::json get_inventory_data() const;

    /**
     * @brief Obtener la información para persistir a un jugador.
     *
     * ```
     * {
     *     "alive": true,
     *     "armor_id": 101,
     *     "body_id": 2,
     *     "class_type": 4,
     *     "curr_exp": 131000,
     *     "curr_hp": 117,
     *     "curr_level": 16,
     *     "curr_mp": 77,
     *     "head_id": 2,
     *     "helmet_id": 2,
     *     "inventory": {
     *         "curr_gold": 0,
     *         "items_ids": [
     *             401,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0
     *         ],
     *         "items_stacks": [
     *             1200,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0,
     *             0
     *         ]
     *     },
     *     "name": "tai",
     *     "race_type": 3,
     *     "shield_id": 201,
     *     "weapon_id": 302
     * }
     * ```
     *
     * @return nlohmann::json
     */
    nlohmann::json get_persist_data() const;
};

#endif  // PLAYER_H