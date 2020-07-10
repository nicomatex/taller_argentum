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
    std::string name = entity_info["name"];
    name[0] = std::toupper(name[0]);
    player.add_component<VisualCharacterComponent>(
        entity_info["head_id"], entity_info["body_id"],
        entity_info["weapon_id"], entity_info["shield_id"],
        entity_info["helmet_id"], entity_info["armor_id"],
        entity_info["move_speed"], name);
    player.add_component<StatsComponent>(
        entity_info["max_hp"], entity_info["curr_hp"], entity_info["max_mp"],
        entity_info["curr_mp"], entity_info["limit_exp"],
        entity_info["curr_exp"], entity_info["curr_level"]);
    player.add_component<SoundComponent>();
    return player;
}

Entity &EntityFactory::create_npc(nlohmann::json entity_info) {
    Entity &npc =
        EntityManager::get_instance().create(entity_info["entity_id"]);
    std::string name = entity_info["name"];
    name[0] = std::toupper(name[0]);
    npc.add_component<PositionComponent>(10, 10);
    npc.add_component<VisualNPCComponent>(entity_info["sprite_id"],
                                          entity_info["move_speed"], name);
    return npc;
}