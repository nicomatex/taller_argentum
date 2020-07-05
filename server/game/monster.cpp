#include "monster.h"

#include "../server_manager.h"
#include "items/item_factory.h"
#include "map.h"
#include "monster_combat_component.h"
#include "monster_movement_component.h"
#include "random_event_generator.h"

Monster::Monster(EntityId entity_id, nlohmann::json monster_info, Map& map)
    : Entity(entity_id, monster_info["name"],
             new MonsterMovementComponent(monster_info["movement_speed"], map,
                                          entity_id),
             new MonsterCombatComponent(
                 monster_info["max_hp"], monster_info["damage"],
                 monster_info["attack_speed"], map, entity_id),
             1, 0),
      map(map),
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
    return entity_data;
}

void Monster::die() {
    switch (RandomEventGenerator::roll()) {
        case rand_gold:
            std::cerr << "Monster dropped "
                      << int(0.2 * combat_component->get_max_hp()) << " gold"
                      << std::endl;
            break;
        case rand_potion:
            std::cerr << "Monster dropped a potion" << std::endl;
            break;
        case rand_item:
            std::cerr << "Monster dropped a random item" << std::endl;
            break;
    }
    alive = false;
}

bool Monster::is_alive() const {
    return alive;
}

void Monster::update(uint64_t delta_t) {
    position_t displacement = movement_component->update(delta_t);
    map.move(id, displacement);
    combat_component->update(delta_t);
}
