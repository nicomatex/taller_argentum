#ifndef MAP_CHANGER_H
#define MAP_CHANGER_H

#include <unordered_map>

#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "game/position.h"

class MapChanger {
   private:
    MapId upper_map;
    MapId lower_map;
    MapId right_map;
    MapId left_map;
    int height;
    int width;
    std::unordered_map<position_t, position_t, PositionHasher,
                       PositionComparator>
        dest_position;
    std::unordered_map<position_t, MapId, PositionHasher, PositionComparator>
        dest_map;
    std::unordered_map<std::string, position_t> change_required;

    bool requires_map_change(position_t position);

    position_t get_dest_position(position_t position);
    MapId get_dest_map(position_t position);

   public:
    MapChanger(nlohmann::json changes, int height, int width);
    ~MapChanger();

    void set_change_if_necessary(const std::string& name, position_t position);

    void change_maps();
};

#endif  // MAP_CHANGER_H
