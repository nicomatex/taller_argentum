#ifndef __INVENTORY_BUFFER_H
#define __INVENTORY_BUFFER_H
#include "../include/nlohmann/json.hpp"
#include "views/game_view/inventory.h"
#include <mutex>

/**
 * @brief Buffer en el cual se almacena la informacion
 * del inventario recibida.
 * 
 */
class InventoryBuffer{
    private:
        nlohmann::json inventory_data;
        std::mutex m;

    public:
        InventoryBuffer();
        ~InventoryBuffer();
        
        /**
         * @brief Agrega una nueva actualizacion del inventario al buffer.
         * 
         * @param new_nventory_data Nueva informacion del inventario.
         */
        void push(nlohmann::json new_nventory_data);

        /**
         * @brief Devuelve la informacion del inventario almacenada.
         * 
         * @return nlohmann::json 
         */
        nlohmann::json get_inventory_data();
};

#endif