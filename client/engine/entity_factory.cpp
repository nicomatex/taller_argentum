#include "entity_factory.h"

#include "ECS/entity.h"
#include "components/position_component.h"
#include "components/sound_component.h"
#include "components/stats_component.h"
#include "components/visual_character_component.h"
#include "components/visual_npc_component.h"

Entity &EntityFactory::create_player(nlohmann::json entity_info) {
    Entity &player =
        EntityManager::get_instance().create(entity_info["entity_id"]);
    player.add_component<PositionComponent>(10, 10);
    player.add_component<VisualCharacterComponent>(
        entity_info["head_id"], entity_info["body_id"],
        entity_info["weapon_id"], entity_info["shield_id"],
        entity_info["helmet_id"], entity_info["armor_id"],
        entity_info["move_speed"]);
    player.add_component<StatsComponent>(130, 80, 100, 30);
    player.add_component<SoundComponent>();
    std::cout << "Added player with entity_id " << entity_info["entity_id"]
              << std::endl;
    return player;
}

Entity &EntityFactory::create_npc(nlohmann::json entity_info) {
    Entity &npc =
        EntityManager::get_instance().create(entity_info["entity_id"]);
    npc.add_component<PositionComponent>(10, 10);
    npc.add_component<VisualNPCComponent>(entity_info["body_id"],
                                                entity_info["move_speed"]);
    npc.add_component<StatsComponent>(130, 80, 100, 30);
    std::cout << "Added npc with entity_id " << entity_info["entity_id"]
              << std::endl;
    return npc;
}