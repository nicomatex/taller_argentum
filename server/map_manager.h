#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <unordered_map>

#include "../include/blocking_queue.h"
#include "../include/types.h"
#include "game/map.h"
#include "game/map_transitions.h"
#include "map_monitor.h"

class MapManager {
   private:
    std::unordered_map<MapId, MapMonitor> maps;
    BlockingQueue<map_change_t> changes_queue;

   public:
    MapManager(const char* path);
    ~MapManager();

    MapMonitor& operator[](MapId map_id);

    const std::vector<MapId> get_ids();

    void update(uint64_t delta_t);

    map_change_t get_change();

    void close() {
        changes_queue.close();
    }
};

#endif  // MAP_MANAGER_H
