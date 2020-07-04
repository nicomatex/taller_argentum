#include "map.h"

#include <iostream>  //temp
#include <mutex>
#include <queue>
#include <unordered_set>

#include "player.h"

Map::Map(nlohmann::json map_description)
    : map_id(map_description["map_id"]),
      dirty(false),
      width(map_description["width"]),
      height(map_description["height"]),
      transitions(map_description["transitions"], width, height),
      entity_factory(*this) {
    for (auto& layer : map_description["layers"].items()) {
        if (layer.value()["name"] == "Collision") {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
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

void Map::add_entity(Entity* entity, position_t position) {
    position = get_nearest_free_position(position);
    dirty = true;
    position_map[entity->get_id()] = position;
    entity_matrix[position] = entity;
    entity_map.emplace(entity->get_id(), entity);
    std::cout << "Added entity with id " << entity->get_id() << std::endl;
}

bool Map::collides(position_t position) {
    if (collision_map.count(position) > 0)
        return true;
    if (position.x < 0 || position.y < 0 || position.x >= width ||
        position.y >= height) {
        return true;
    }
    if (entity_matrix.count(position))
        return true;
    return false;
}

void Map::move(EntityId entity_id, position_t steps) {
    if (steps.x == 0 && steps.y == 0)
        return;
    position_t new_position = position_map[entity_id];
    Entity* entity = entity_map.at(entity_id);

    new_position.x += steps.x;
    new_position.y += steps.y;

    if (entity->get_type() == PLAYER && transitions.is_transition(new_position))
        transitions.push_change(entity->get_name(), new_position);
    if (collides(new_position))
        return;

    // Borrado de la matriz de entidad en la vieja posicion.
    position_t old_position = position_map[entity_id];
    entity_matrix.erase(old_position);

    // Agregado en la matriz de entidad y mapa de posiciones en la nueva
    // posicion.
    entity_matrix[new_position] = entity;
    position_map[entity_id] = new_position;
}

std::queue<map_change_t>& Map::get_transitions() {
    return transitions.get_changes();
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

nlohmann::json Map::add_player(nlohmann::json player_info) {
    Player* player = entity_factory.create_player(player_info);

    add_entity(player, player_info["pos"]);

    player_info = player->get_data();
    player_info["inventory"] = player->get_inventory_data();
    return player_info;
}

nlohmann::json Map::rm_player(EntityId entity_id) {
    Player* player = static_cast<Player*>(entity_map.at(entity_id));
    entity_map.erase(entity_id);
    nlohmann::json player_data = player->get_persist_data();
    position_t position = position_map.at(entity_id);
    position_map.erase(entity_id);
    entity_matrix.erase(position);
    player_data["pos"] = position;
    delete player;
    return player_data;
}

position_t Map::get_position(EntityId entity_id) {
    return position_map.at(entity_id);
}

void Map::update(uint64_t delta_t) {
    while (!actions.empty()) {
        entity_action_t ent_act = actions.front();
        actions.pop();
        ent_act.action->execute(*this, ent_act.entity);
        delete ent_act.action;
    }
    for (auto& it : entity_map) {
        it.second->update(delta_t);
    }
}

void Map::push_log(const nlohmann::json& log) {
    update_logs.push(log);
}

void Map::push_action(EntityId entity_id, Action* action) {
    actions.push({entity_id, action});
}

std::queue<nlohmann::json>& Map::get_update_logs() {
    return update_logs;
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
