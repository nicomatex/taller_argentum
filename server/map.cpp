#include "map.h"

Map::Map() {}

void Map::add_entity(unsigned int entity_id, position_t position) {
    position_map[entity_id] = position;
    entity_matrix[position.x][position.y].emplace(entity_id);
}

bool Map::collides(position_t position) {
    // TODO
    return false;
}

void Map::move(unsigned int entity_id, Direction direction) {
    position_t new_position = position_map[entity_id];
    switch (direction) {
        case UP:
            new_position.y -= 1;
            break;
        case DOWN:
            new_position.y += 1;
            break;
        case RIGHT:
            new_position.x += 1;
            break;
        case LEFT:
            new_position.x -= 1;
            break;
    }
    if (collides(new_position))
        return;

    // Borrado de la matriz de entidad en la vieja posicion.
    position_t old_position = position_map[entity_id];
    entity_matrix[old_position.x][old_position.y].erase(entity_id);

    // Agregado en la matriz de entidad y mapa de posiciones en la nueva
    // posicion.
    entity_matrix[new_position.x][new_position.y].emplace(entity_id);
    position_map[entity_id] = new_position;
}

PositionMap Map::get_position_map() {
    return position_map;
}

Map::~Map() {}
