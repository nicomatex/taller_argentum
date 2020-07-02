#ifndef __PLAYER_H
#define __PLAYER_H
#include <string>

#include "entity.h"
#include "inventory.h"
#include "map.h"
#include "position.h"

class Player : public Entity {
   private:
    // ExperienceComponent

    const int head_id;
    const int body_id;

    Inventory inventory;

    Map &map;  // Mapa en el que esta el jugador en este momento.
               // STATS
               // INVENTARIO
   public:
    Player(EntityId entity_id, nlohmann::json player_info, Map &map);
    entity_type_t get_type() const override;
    nlohmann::json get_data() const override;
    nlohmann::json get_persist_data() const override;

    void set_movement(mov_action_t action, direction_t direction);
    void update(uint64_t delta_t) override;
};

#endif