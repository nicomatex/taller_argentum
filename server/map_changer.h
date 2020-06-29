#ifndef MAP_CHANGER_H
#define MAP_CHANGER_H

#include <unordered_map>

#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "game/map_transitions.h"
#include "game/position.h"

class MapChanger {
   private:
    std::queue<map_change_t> changes_queue;

   public:
    MapChanger();
    ~MapChanger();

    void push_change(map_change_t change);

    void change_maps();
};

#endif  // MAP_CHANGER_H
