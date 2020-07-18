#include "entity_factory.h"

#include "../game_manager.h"
#include "player.h"

EntityId EntityFactory::get_next_id() {
    static EntityId entity_id = 0;
    return entity_id++;
}

EntityFactory::EntityFactory(Map& map) : map(map) {}
EntityFactory::~EntityFactory() {}

Player* EntityFactory::create_player(nlohmann::json player_info) {
    return new Player(get_next_id(), player_info, map);
}

Monster* EntityFactory::create_monster(const std::string& monster_name) {
    GameManager& game_manager = GameManager::get_instance();
    MobFactory& mob_factory = game_manager.get_mob_factory();
    return mob_factory.create_monster(get_next_id(), monster_name, map);
}

Monster* EntityFactory::create_monster(MobId monster_id) {
    GameManager& game_manager = GameManager::get_instance();
    MobFactory& mob_factory = game_manager.get_mob_factory();
    return mob_factory.create_monster(get_next_id(), monster_id, map);
}

Npc* EntityFactory::create_npc(npc_proffesion_t npc) {
    GameManager& game_manager = GameManager::get_instance();
    MobFactory& mob_factory = game_manager.get_mob_factory();
    return mob_factory.create_npc(get_next_id(), npc, map);
}

Npc* EntityFactory::create_npc(MobId npc_id) {
    GameManager& game_manager = GameManager::get_instance();
    MobFactory& mob_factory = game_manager.get_mob_factory();
    return mob_factory.create_npc(get_next_id(), npc_id, map);
}
