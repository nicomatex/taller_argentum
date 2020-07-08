#ifndef __LOOT_BUFFER_H
#define __LOOT_BUFFER_H

#include <mutex>

#include "../include/nlohmann/json.hpp"
#include "engine/map.h"

/**
 * @brief Buffer donde se almacenan los items tirados en el piso.
 *
 */
class LootBuffer {
   private:
    std::mutex m;
    nlohmann::json loot_info;

   public:
    LootBuffer();
    ~LootBuffer();

    /**
     * @brief Carga informacion en el buffer.
     *
     * @param new_loot_info Nueva informacion a cargar en el buffer.
     */
    void load_buffer(nlohmann::json new_loot_info);

    /**
     * @brief Flushea la informacion del loot en un mapa.
     *
     * @param map Mapa sobre el cual se descargara la informacion.
     */
    void flush(Map &map);
};

#endif