#ifndef MAP_TRANSITIONS_H
#define MAP_TRANSITIONS_H

#include <queue>
#include <unordered_map>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "position.h"

typedef struct map_change {
    std::string name;
    MapId map;
    position_t position;
} map_change_t;

class MapTransitions {
   private:
    std::queue<map_change_t> changes_queue;
    std::unordered_map<position_t, std::pair<MapId, position_t>, PositionHasher,
                       PositionComparator>
        teleports;

   public:
    MapTransitions(nlohmann::json changes, int width, int height);
    ~MapTransitions();

    bool is_transition(position_t position);

    void push_change(std::string name, position_t position);

    std::queue<map_change_t>& get_changes();
};

#endif  // MAP_TRANSITIONS_H
