#include "map.h"

#include <iostream>  //temp
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

EntityId Map::get_next_id() {
    static EntityId entity_id = 0;
    return entity_id++;
}

void Map::add_entity(Entity* entity, position_t position) {
    std::unique_lock<std::mutex> l(m);
    position_map[entity->get_id()] = position;
    entity_matrix[position.x][position.y].emplace(entity->get_id());
    entity_map[entity->get_id()] = entity;
}

bool Map::collides(position_t position) {
    std::unique_lock<std::mutex> l(m);
    if (collision_map.count(position) > 0)
        return true;
    if (entity_matrix[position.x][position.y].size() > 0)
        return true;
    return false;
}

void Map::move(EntityId entity_id, steps_t steps) {
    std::unique_lock<std::mutex> l(m);
    position_t new_position = position_map[entity_id];

    new_position.x += steps.x;
    new_position.y += steps.y;

    if (collides(new_position))
        return;

    // Borrado de la matriz de entidad en la vieja posicion.
    position_t old_position = position_map[entity_id];
    entity_matrix[old_position.x][old_position.y].erase(entity_id);

    // Agregado en la matriz de entidad y mapa de posiciones en la nueva
    // posicion.
    entity_matrix[new_position.x][new_position.y].emplace(entity_id);
    position_map[entity_id] = new_position;
    std::cerr << "Moved player to " << new_position.x << " - " << new_position.y
              << std::endl;
}

EntityId Map::add_player(ClientId client_id, nlohmann::json player_info) {
    EntityId entity_id = get_next_id();
    Player* player =
        new Player(entity_id, int(player_info["id_head"]),
                   int(player_info["id_body"]), player_info["name"], *this);
    position_t player_position = {int(player_info["pos"]["x"]),
                                  int(player_info["pos"]["y"])};
    add_entity(player, player_position);
    client_map[client_id] = entity_id;

    std::cerr << "Added player with clientid " << client_id << " - entity id "
              << entity_id << std::endl;

    return entity_id;
}

void Map::update(uint64_t delta_t) {
    std::unique_lock<std::mutex> l(m);
    for (auto& it : entity_map) {
        it.second->update(delta_t);
    }
}

Player& Map::get_player(ClientId client_id) {
    return *(Player*)entity_map.at(client_map.at(client_id));
}

nlohmann::json Map::get_position_data() {
    return nlohmann::json(position_map);
}

nlohmann::json Map::get_entity_data() {
    return nlohmann::json{};
}

nlohmann::json Map::get_map_data() {
    return visual_map_info;
}

Map::~Map() {}
