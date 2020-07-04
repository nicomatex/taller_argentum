#ifndef __INVENTORY_BUFFER_H
#define __INVENTORY_BUFFER_H
#include "../include/nlohmann/json.hpp"
#include "views/game_view/inventory.h"
#include <mutex>

class InventoryBuffer{
    private:
        nlohmann::json inventory_data;
        std::mutex m;

    public:
        InventoryBuffer();
        ~InventoryBuffer();

        void push(nlohmann::json new_nventory_data);
        nlohmann::json get_inventory_data();
};

#endif