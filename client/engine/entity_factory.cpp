#include "entity_factory.h"

#include "ECS/entity.h"
#include "components/position_component.h"
#include "components/visual_character_component.h"

Entity &EntityFactory::create_player(unsigned int entity_id, int head_id,
                                     int body_id, int weapon_id, int shield_id,
                                     int helmet_id, int armor_id) {
    Entity &player = EntityManager::get_instance().create(entity_id);
    player.add_component<PositionComponent>(10, 10);
    player.add_component<VisualCharacterComponent>(
        head_id, body_id, weapon_id, shield_id, helmet_id, armor_id, 7);
    std::cout << "Added player with entity_id " << entity_id << std::endl;
    return player;
}

Entity &EntityFactory::create_player(nlohmann::json entity_info) {
    return create_player(entity_info["entity_id"], entity_info["head_id"],
                         entity_info["body_id"], entity_info["weapon_id"],
                         entity_info["shield_id"], entity_info["helmet_id"],
                         entity_info["armor_id"]);
}