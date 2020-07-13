#ifndef __MAP_DECORATIONS_BUFFER_H
#define __MAP_DECORATIONS_BUFFER_H

#include <mutex>
#include <queue>

#include "../include/nlohmann/json.hpp"
#include "engine/map.h"

/**
 * @brief Buffer donde se almacenan los items tirados en el piso.
 *
 */
class MapDecorationsBuffer {
   private:
    std::mutex m;
    nlohmann::json loot_info;
    std::queue<nlohmann::json> special_ability_queue;

   public:
    MapDecorationsBuffer();
    ~MapDecorationsBuffer();

    /**
     * @brief Carga informacion en el buffer.
     *
     * @param new_loot_info Nueva informacion a cargar en el buffer.
     */
    void load_loot_info(nlohmann::json new_loot_info);


    /**
     * @brief Agrega informacion sobre una habilidad especial.
     * 
     * @param ability_info Informacion de la habilidad especial.
     */
    void push_special_ability(nlohmann::json ability_info);

    /**
     * @brief Flushea la informacion del loot en un mapa.
     *
     * @param map Mapa sobre el cual se descargara la informacion.
     */
    void flush_loot(Map &map);

    /**
     * @brief Flushea informacion de habilidades especiales en un mapa.
     * 
     * @param map Mapa sobre el cual se descargara la informacion.
     */
    void flush_special_abilities(Map &map);
};

#endif