#include "entity_factory.h"

#include "../server_manager.h"
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

Monster* EntityFactory::create_monster(MonsterId monster_id) {
    return ServerManager::get_instance().get_monster_factory().create_monster(
        get_next_id(), monster_id, map);
}
