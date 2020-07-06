#ifndef __LOOT_BUFFER_H
#define __LOOT_BUFFER_H

#include <mutex>
#include "engine/map.h"
#include "../include/nlohmann/json.hpp"

class LootBuffer{
    private:
        std::mutex m;
        nlohmann::json loot_info;
    public:
        LootBuffer();
        ~LootBuffer();
        void load_buffer(nlohmann::json new_loot_info);
        void flush(Map &map);
};


#endif