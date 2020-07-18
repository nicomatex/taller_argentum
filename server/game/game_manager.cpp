#include "game_manager.h"

#include "../../include/my_exception.h"
#include "attribute_manager.h"
#include "configuration_manager.h"
#include "race_graphics_manager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(const char* items_index_path,
                         const char* mobs_index_path,
                         const char* maps_index_path)
    : item_factory(items_index_path),
      mob_factory(mobs_index_path),
      map_manager(maps_index_path),
      game_loop(map_manager) {
    instance = this;
    AttributeManager::init("ind/stats.json", "ind/races.json",
                           "ind/classes.json");
    RaceGraphicsManager::init("ind/races_graphics.json");
    ConfigurationManager::init("ind/config.json");
}

GameManager::~GameManager() {}

GameManager& GameManager::get_instance() {
    if (!instance)
        throw MyException("Game manager is not started.");
    return *instance;
}

void GameManager::start() {
    map_manager.create_maps();
    game_loop.start();
}

ItemFactory& GameManager::get_item_factory() {
    return item_factory;
}

MobFactory& GameManager::get_mob_factory() {
    return mob_factory;
}

MapManager& GameManager::get_map_manager() {
    return map_manager;
}

void GameManager::finish() {
    map_manager.close();
    game_loop.stop();
    game_loop.join();
}
