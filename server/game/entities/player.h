#ifndef PLAYER_H
#define PLAYER_H
#include <string>

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

    Map& map;  // Mapa en el que esta el jugador en este momento.
    class_type_t class_type;
    race_type_t race_type;

   public:
    Player(EntityId entity_id, nlohmann::json player_info, Map& map);

    entity_type_t get_type() const override;
    class_type_t get_class_type() const;
    race_type_t get_race_type() const;

    void die() override;
    bool is_alive() const override;

    void use(SlotId slot);
    void add_item(Item* item);

    void set_movement(mov_action_t action, direction_t direction);
    void update(uint64_t delta_t) override;

    nlohmann::json get_data() const override;
    nlohmann::json get_inventory_data() const;
    nlohmann::json get_persist_data() const;
};

#endif  // PLAYER_H