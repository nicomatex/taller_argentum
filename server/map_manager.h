#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <unordered_map>

#include "../include/types.h"
#include "game/map.h"
#include "game/map_transitions.h"
#include "map_monitor.h"

class MapManager {
   private:
    std::unordered_map<MapId, MapMonitor> maps;
    MapChanger map_changer;

   public:
    MapManager(const char* path);

    MapMonitor& operator[](MapId map_id);

    const std::vector<MapId> get_ids();

    void update(uint64_t delta_t);

    ~MapManager();
};

#endif  // MAP_MANAGER_H
