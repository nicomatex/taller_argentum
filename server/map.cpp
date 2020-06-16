#include "map.h"

#include <mutex>

#include "player.h"

Map::Map(nlohmann::json map_description) {
    int height = map_description["height"];
    int width = map_description["width"];

    for (auto& layer : map_description["layers"].items()) {
        if (layer.value()["name"] == "Collision") {
            for (unsigned int i = 0; i < height; i++) {
                for (unsigned int j = 0; j < width; j++) {
                    int tile_index = j + (i * width);
                    if (int(layer.value()["data"][tile_index]) != 0) {
                        collision_map.insert({i, j});
                    }
                }
            }
            map_description["layers"].erase(std::stoi(layer.key()));
        }
    }
    visual_map_info = map_description;
}

int Map::get_next_id() {
    static int entity_id = 0;
    entity_id++;
    return entity_id;
}

void Map::add_entity(Entity* entity, position_t position) {
    std::unique_lock<std::mutex> l(m);
    position_map[entity->get_id()] = position;
    entity_matrix[position.x][position.y].emplace(entity->get_id());
    entity_map[entity->get_id()] = entity;
}

bool Map::collides(position_t position) {
    std::unique_lock<std::mutex> l(m);
    if(collision_map.count(position) > 0) return false;
    if(entity_matrix[position.x][position.y].size() > 0) return false;
    return true;
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

int Map::add_player(nlohmann::json player_info, int client_id) {
    int entity_id = get_next_id();
    Player* player =
        new Player(entity_id, int(player_info["id_head"]), int(player_info["id_body"]),
                   player_info["name"], *this);
    position_t player_position = player_info["position"];
    add_entity(player,player_position);
    client_map[client_id] = entity_id;
}

void Map::update(unsigned int delta_t){
    std::unique_lock<std::mutex> l(m);
    for(auto &it : entity_map){
        it.second->update(delta_t);
    }
}

nlohmann::json Map::get_map_data(){
    return visual_map_info;
}

PositionMap Map::get_position_map() {
    // Esto sirve despues para el polling a la hora de enviarle
    // info a los jugadores.
    std::unique_lock<std::mutex> l(m);
    return position_map;
}

Map::~Map() {}
