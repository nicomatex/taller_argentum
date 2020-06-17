#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <unordered_map>

#include "../include/types.h"
#include "map.h"

class MapManager {
   private:
    std::unordered_map<MapId, Map> maps;

   public:
    MapManager(const char* path);

    Map& operator[](MapId map_id);

    const std::vector<MapId> get_ids();

    void update(uint64_t delta_t);

    ~MapManager();
};

#endif  // MAP_MANAGER_H
