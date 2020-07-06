#ifndef MAP_CHANGER_H
#define MAP_CHANGER_H

#include <unordered_map>

#include "game/map_transitions.h"

class MapChanger {
   public:
    MapChanger();
    ~MapChanger();

    void push_change(map_change_t change);
};

#endif  // MAP_CHANGER_H
