#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <unordered_map>

#include "../../include/blocking_queue.h"
#include "../../include/types.h"
#include "map_monitor.h"
#include "map_transitions.h"

class MapManager {
   private:
    const char* index_path;
    std::unordered_map<MapId, MapMonitor> maps;
    BlockingQueue<map_change_t> changes_queue;

   public:
    MapManager(const char* index_path);
    ~MapManager();

    void create_maps();

    MapMonitor& operator[](MapId map_id);

    const std::vector<MapId> get_ids();

    void update(uint64_t delta_t);

    map_change_t get_change();

    void close();
};

#endif  // MAP_MANAGER_H
