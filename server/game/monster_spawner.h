#ifndef MONSTER_SPAWNER_H
#define MONSTER_SPAWNER_H

#include <string>
#include <unordered_map>
#include <utility>

#include "../../include/nlohmann/json.hpp"
#include "position.h"

/**
 * @brief Intervalo de tiempo para el __spawn__ de mosntruos (en ms).
 *
 */
#define SPAWN_INTERVAL 15000

class Map;

class MonsterSpawner {
   private:
    std::unordered_map<std::string, std::pair<int, position_t>> spawn_points;
    Map& map;
    uint64_t accumulator;

    std::unordered_map<std::string, int> search_monsters();
   public:
    MonsterSpawner(Map& map, const nlohmann::json& spawn_list);
    ~MonsterSpawner();

    MonsterSpawner(Map& map, const MonsterSpawner& other);

    void update(uint64_t delta_t);
};

#endif  // MONSTER_SPAWNER_H
