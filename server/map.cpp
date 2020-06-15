#include "map.h"

#include <mutex>

Map::Map(nlohmann::json map_description) {
    int height = map_description["height"];
    int width = map_description["width"];

    for (auto& layer : map_description["layers"].items()) {
        if (layer.value()["name"] == "Collision") {
            for (unsigned int i = 0; i < height; i++) {
                for (unsigned int j = 0; j < width; j++) {
                    int tile_index = j + (i * width);
                    if (int(layer.value()["data"][tile_index]) != 0) {
                        collision_map.insert({i,j});
                    }
                }
            }
            map_description["layers"].erase(std::stoi(layer.key()));
        }
    }
    visual_map_info = map_description;
}

void Map::add_entity(unsigned int entity_id, position_t position) {
    std::unique_lock<std::mutex> l(m);
    position_map[entity_id] = position;
    entity_matrix[position.x][position.y].emplace(entity_id);
}

bool Map::collides(position_t position) {
    std::unique_lock<std::mutex> l(m);
    return collision_map.count(position);
}

void Map::move(unsigned int entity_id, steps_t steps) {
    std::unique_lock<std::mutex> l(m);
    position_t new_position = position_map[entity_id];

    new_position.x += steps.x;
    new_position.y += steps.y;

    if (collides(new_position)) return;

    // Borrado de la matriz de entidad en la vieja posicion.
    position_t old_position = position_map[entity_id];
    entity_matrix[old_position.x][old_position.y].erase(entity_id);

    // Agregado en la matriz de entidad y mapa de posiciones en la nueva
    // posicion.
    entity_matrix[new_position.x][new_position.y].emplace(entity_id);
    position_map[entity_id] = new_position;
}

PositionMap Map::get_position_map() {
    // Esto sirve despues para el polling a la hora de enviarle
    // info a los jugadores.
    std::unique_lock<std::mutex> l(m);
    return position_map;
}

Map::~Map() {}
