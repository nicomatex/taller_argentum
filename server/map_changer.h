#ifndef MAP_CHANGER_H
#define MAP_CHANGER_H

#include <unordered_map>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "position.h"

class MapChanger {
   private:
    std::unordered_map<position_t, position_t, PositionHasher,
                       PositionComparator>
        dest_position;
    std::unordered_map<position_t, MapId, PositionHasher, PositionComparator>
        dest_map;
    std::unordered_map<std::string, position_t> change_required;

   public:
    MapChanger(nlohmann::json teleports);
    ~MapChanger();

    void set_change_if_necessary(const std::string& name, position_t position);

    void change_maps();
};

#endif  // MAP_CHANGER_H
