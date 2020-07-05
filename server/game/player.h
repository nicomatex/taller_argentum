#ifndef PLAYER_H
#define PLAYER_H
#include <string>

#include "../attribute_manager.h"
#include "entity.h"
#include "inventory.h"
#include "map.h"
#include "position.h"

class Player : public Entity {
   private:
    const int head_id;
    const int body_id;

    Inventory inventory;

    Map& map;  // Mapa en el que esta el jugador en este momento.
    class_type_t class_type;
    race_type_t race_type;

   public:
    Player(EntityId entity_id, nlohmann::json player_info, Map& map);
    entity_type_t get_type() const override;
    nlohmann::json get_data() const override;
    nlohmann::json get_inventory_data() const;
    nlohmann::json get_persist_data() const;
    class_type_t get_class_type() const;
    race_type_t get_race_type() const;
    unsigned int get_level() const;
    void use(SlotId slot);

    void set_movement(mov_action_t action, direction_t direction);
    void update(uint64_t delta_t) override;
};

#endif  // PLAYER_H