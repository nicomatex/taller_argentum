#include "map.h"

#include <iostream>  //temp
#include <mutex>
#include <queue>
#include <unordered_set>

#include "player.h"

Map::Map(nlohmann::json map_description) : dirty(false) {
    int height = map_description["height"];
    int width = map_description["width"];

    for (auto& layer : map_description["layers"].items()) {
        if (layer.value()["name"] == "Collision") {
            for (unsigned int i = 0; i < height; i++) {
                for (unsigned int j = 0; j < width; j++) {
                    int tile_index = j + (i * width);
                    if (int(layer.value()["data"][tile_index]) != 0) {
                        collision_map.insert({j, i});
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
    dirty = true;
    position_map[entity->get_id()] = position;
    entity_matrix[position.x][position.y].emplace(entity->get_id());
    entity_map.emplace(entity->get_id(), entity);
    std::cout << "Added entity with id " << entity->get_id() << std::endl;
}

bool Map::collides(position_t position) {
    if (collision_map.count(position) > 0)
        return true;
    if (entity_matrix[position.x][position.y].size() > 0)
        return true;
    if (position.x <= 0 || position.y <= 0 || position.x >= MAP_SIZE - 1 ||
        position.y >= MAP_SIZE - 1) {
        return true;
    }
    return false;
}

void Map::move(EntityId entity_id, steps_t steps) {
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

position_t Map::get_nearest_free_position(position_t position) {
    if (!collides(position))
        return position;
    std::queue<position_t> queue;
    std::unordered_set<position_t, PositionHasher, PositionComparator> visited;
    queue.push(position);
    while (!queue.empty()) {
        position_t p = queue.front();
        queue.pop();
        if (visited.count(p))
            continue;
        visited.emplace(p);
        position_t aux = {p.x + 1, p.y};
        if (!collides(aux))
            return aux;
        else
            queue.push(aux);
        aux = {p.x, p.y + 1};
        if (!collides(aux))
            return aux;
        else
            queue.push(aux);
        aux = {p.x - 1, p.y};
        if (!collides(aux))
            return aux;
        else
            queue.push(aux);
        aux = {p.x, p.y - 1};
        if (!collides(aux))
            return aux;
        else
            queue.push(aux);
    }

    return position;
}

EntityId Map::add_player(nlohmann::json player_info) {
    EntityId entity_id = get_next_id();
    Player* player =
        new Player(entity_id, int(player_info["head_id"]),
                   int(player_info["body_id"]), player_info["name"], *this);
    position_t player_position = player_info["pos"];
    position_t nearest_position = get_nearest_free_position(player_position);

    add_entity(player, nearest_position);

    return entity_id;
}

nlohmann::json Map::rm_player(EntityId entity_id) {
    Entity* player = entity_map.at(entity_id);
    entity_map.erase(entity_id);
    nlohmann::json player_data = player->get_data();
    position_t position = position_map.at(entity_id);
    position_map.erase(entity_id);
    collision_map.erase(position);
    entity_matrix[position.x][position.y].erase(entity_id);
    player_data["pos"] = position;
    return player_data;
}

void Map::update(uint64_t delta_t) {
    for (auto& it : entity_map) {
        it.second->update(delta_t);
    }
}

void Map::with_entity(EntityId entity_id, const Action& action) {
    action.execute(*(entity_map.at(entity_id)));
}

nlohmann::json Map::get_position_data(const PositionMap& position_map) {
    nlohmann::json positions = nlohmann::json::array();
    for (auto& it : position_map) {
        positions.push_back(
            {{"entity_id", it.first}, {"x", it.second.x}, {"y", it.second.y}});
    }
    return positions;
}

const PositionMap Map::get_position_map() const {
    return position_map;
}

nlohmann::json Map::get_entity_data() {
    nlohmann::json entities;
    entities = nlohmann::json::array();
    for (auto& it : entity_map) {
        entities.push_back(it.second->get_data());
    }
    return entities;
}

nlohmann::json Map::get_map_data() {
    return visual_map_info;
}

bool Map::is_dirty() const {
    return dirty;
}

Map::~Map() {}
