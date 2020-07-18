#include "monster.h"

#include <vector>

#include "../game_manager.h"
#include "../items/item_factory.h"
#include "../map.h"
#include "../random_event_generator.h"
#include "components/monster_combat_component.h"
#include "components/monster_movement_component.h"

Monster::Monster(EntityId entity_id, nlohmann::json monster_info, Map& map)
    : Entity(entity_id, map, monster_info["name"],
             new MonsterMovementComponent(monster_info["movement_speed"], map,
                                          entity_id),
             new MonsterCombatComponent(
                 monster_info["max_hp"], monster_info["damage"],
                 monster_info["attack_speed"], map, entity_id),
             25, 0),
      sprite_id(monster_info["sprite_id"]),
      alive(true) {}

entity_type_t Monster::get_type() const {
    return MONSTER;
}

nlohmann::json Monster::get_data() const {
    nlohmann::json entity_data;
    entity_data["entity_id"] = get_id();
    entity_data["type_id"] = get_type();
    entity_data["name"] = get_name();
    entity_data["sprite_id"] = sprite_id;
    nlohmann::json aux = movement_component->get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    aux = combat_component->get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    aux = experience_component.get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    return entity_data;
}

void Monster::die() {
    GameManager& game_manager = GameManager::get_instance();
    ItemFactory& item_factory = game_manager.get_item_factory();
    Item* item = nullptr;
    switch (RandomEventGenerator::roll()) {
        case rand_gold:
            item = item_factory.create(
                500, int(0.2 * combat_component->get_max_hp()));
            break;
        case rand_potion: {
            std::vector<ItemId> vec = {400, 401};
            unsigned int idx =
                RandomEventGenerator::rand_idx_in_vec(vec.size());
            item = item_factory.create(vec[idx], 1);
        } break;
        case rand_item: {
            std::vector<ItemId> vec = {1,   2,   3,   100, 101, 102,
                                       200, 201, 300, 301, 302, 303,
                                       304, 305, 306, 307, 308};
            unsigned int idx =
                RandomEventGenerator::rand_idx_in_vec(vec.size());
            item = item_factory.create(vec[idx], 1);
        } break;
        case nothing:
            break;
        case invalid:
            break;
    }
    if (item)
        map.drop_loot(id, item);
    alive = false;
}

bool Monster::is_alive() const {
    return alive;
}

bool Monster::can_attack(Entity* attacked) const {
    if (!combat_component->attack_ready())
        return false;
    return (attacked->get_type() == PLAYER);
}

void Monster::update(uint64_t delta_t) {
    position_t displacement = movement_component->update(delta_t);
    map.move(id, displacement);
    combat_component->update(delta_t);
}
