#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entities/mob_factory.h"
#include "game_loop.h"
#include "items/item_factory.h"
#include "map_manager.h"
#include "map_monitor.h"

class GameManager {
   private:
    friend class ServerManager;
    static GameManager* instance;

    ItemFactory item_factory;
    MobFactory mob_factory;
    MapManager map_manager;
    GameLoop game_loop;

    GameManager(const char* items_index_path, const char* mobs_index_path,
                const char* maps_index_path);

   public:
    static GameManager& get_instance();
    ~GameManager();

    void start();

    ItemFactory& get_item_factory();
    MobFactory& get_mob_factory();
    MapManager& get_map_manager();

    void finish();
};

#endif  // GAME_MANAGER_H
