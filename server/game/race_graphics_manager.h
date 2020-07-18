#ifndef RACE_GRAPHICS_MANAGER_H
#define RACE_GRAPHICS_MANAGER_H

#include <unordered_map>

#include "../../include/types.h"

class RaceGraphicsManager {
   private:
    static std::unordered_map<race_type_t, uint32_t> race_heads_map;
    static std::unordered_map<race_type_t, uint32_t> race_bodies_map;

   public:
    RaceGraphicsManager();
    ~RaceGraphicsManager();
    static void init(const char *races_file);
    static uint32_t get_race_head(race_type_t race_type);
    static uint32_t get_race_body(race_type_t race_type);
};

#endif  // RACE_GRAPHICS_MANAGER_H