#ifndef MONSTER_SPAWNER_H
#define MONSTER_SPAWNER_H

#include <string>
#include <unordered_map>
#include <utility>

#include "../../include/nlohmann/json.hpp"
#include "position.h"

class Map;

/**
 * @brief Clase que mantiene los "spawns" de monstruos en un mapa.
 *
 * Es inicializada con información de qué, y cuántos monstruos se deben agregar
 * en qué posiciones del mapa.
 *
 */
class MonsterSpawner {
   private:
    std::unordered_multimap<std::string, std::pair<int, position_t>>
        spawn_points;
    Map& map;
    uint64_t accumulator;

    std::unordered_map<std::string, int> search_monsters();

   public:
    MonsterSpawner(Map& map, const nlohmann::json& spawn_list);
    ~MonsterSpawner();

    MonsterSpawner(Map& map, const MonsterSpawner& other) = delete;

    /**
     * @brief Update del MonsterSpawner.
     *
     * Pasado el tiempo definido por la constante, en caso de que haya menos de
     * la cantidad indicada en el archivo de configuración (y si el mapa no es
     * seguro) agrega uno de cada tipo faltante en una posición aleatoria
     * cercana a la dada en la configuración.
     *
     * @param delta_t
     */
    void update(uint64_t delta_t);
};

#endif  // MONSTER_SPAWNER_H
