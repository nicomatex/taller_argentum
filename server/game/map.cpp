#include "map.h"

#include <cstdlib>
#include <iostream>  //temp
#include <mutex>
#include <queue>
#include <unordered_set>

#include "entities/player.h"

Map::Map(MapId map_id, const std::string& map_name, bool is_safe,
         const nlohmann::json& map_description, const nlohmann::json& map_mobs,
         const nlohmann::json& map_transitions)
    : width(map_description["width"]),
      height(map_description["height"]),
      _is_safe(is_safe),
      map_name(map_name),
      healer_pos(map_mobs["healer"]),
      _dirty_entities(false),
      entity_matrix({}),
      _dirty_loot(false),
      transitions(map_id, map_transitions, width, height),
      entity_factory(*this),
      monster_spawner(*this, map_mobs["spawns"]) {
    visual_map_info = map_description;
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
            visual_map_info["layers"].erase(std::stoi(layer.key()));
        }
    }
    Npc* npc = entity_factory.create_npc(BANKER);
    position_t pos = map_mobs["banker"];
    add_entity(npc, pos);
    npc = entity_factory.create_npc(MERCHANT);
    pos = map_mobs["merchant"];
    add_entity(npc, pos);
    npc = entity_factory.create_npc(HEALER);
    add_entity(npc, healer_pos);
    std::cerr << "Adding npcs\n";
}

Map::~Map() {
    for (auto it : entity_matrix) delete it.second;
    for (auto it : loot_matrix) delete it.second;
    while (!actions.empty()) {
        entity_action_t entity_action = actions.front();
        actions.pop();
        delete entity_action.action;
    }
}

const std::string& Map::get_name() {
    return map_name;
}

void Map::add_entity(Entity* entity, position_t position) {
    position = get_nearest_free_position(entity_matrix, position);
    _dirty_entities = true;
    position_map[entity->get_id()] = position;
    entity_matrix[position] = entity;
}

template <typename T>
position_t Map::get_nearest_free_position(ObjectMatrix<T> object_matrix,
                                          position_t position) {
    if (!collides(object_matrix, position))
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
        position_t aux[4] = {
            {p.x + 1, p.y}, {p.x, p.y + 1}, {p.x - 1, p.y}, {p.x, p.y - 1}};
        for (position_t it : aux) {
            if (!collides(object_matrix, it)) {
                return it;
            } else
                queue.push(it);
        }
    }
    return position;
}

template <typename T>
bool Map::collides(ObjectMatrix<T> object_matrix, position_t position) {
    if (collision_map.count(position) > 0)
        return true;
    if (position.x < 0 || position.y < 0 || position.x >= width ||
        position.y >= height) {
        return true;
    }
    if (object_matrix.count(position))
        return true;
    return false;
}

void Map::move(EntityId entity_id, position_t steps) {
    if (steps.x == 0 && steps.y == 0)
        return;
    position_t position = position_map[entity_id];
    Entity* entity = entity_matrix.at(position);

    position.x += steps.x;
    position.y += steps.y;

    if (entity->get_type() == PLAYER)
        transitions.push_if_transition(entity->get_name(), position);
    if (collides(entity_matrix, position))
        return;

    // Borrado de la matriz de entidad en la vieja posicion.
    position_t old_position = position_map[entity_id];
    entity_matrix.erase(old_position);

    // Agregado en la matriz de entidad y mapa de posiciones en la nueva
    // posicion.
    entity_matrix[position] = entity;
    position_map[entity_id] = position;
}

std::queue<map_change_t>& Map::get_transitions() {
    return transitions.get_changes();
}

void Map::teleport(EntityId player_id, position_t dest) {
    if (!position_map.count(player_id))
        return;
    Entity* player = entity_matrix.at(position_map.at(player_id));
    if (player->get_type() != PLAYER)
        return;
    transitions.teleport(player->get_name(), dest);
}

nlohmann::json Map::add_player(nlohmann::json player_info) {
    Player* player = entity_factory.create_player(player_info);

    add_entity(player, player_info["pos"]);

    player_info = player->get_data();
    player_info["inventory"] = player->get_inventory_data();
    return player_info;
}

nlohmann::json Map::rm_player(EntityId entity_id) {
    Player* player =
        static_cast<Player*>(entity_matrix.at(position_map[entity_id]));
    nlohmann::json player_data = player->get_persist_data();
    position_t position = position_map.at(entity_id);
    rm_entity(entity_id);
    player_data["pos"] = position;
    return player_data;
}

void Map::rm_entity(EntityId entity_id) {
    _dirty_entities = true;
    position_t position = position_map.at(entity_id);
    Entity* entity = entity_matrix.at(position);
    entity_matrix.erase(position);
    position_map.erase(entity_id);
    delete entity;
}

bool Map::entity_exists(EntityId entity_id) {
    return position_map.count(entity_id);
}

position_t Map::get_position(EntityId entity_id) {
    return position_map.at(entity_id);
}

position_t Map::get_healer_pos() const {
    return healer_pos;
}

bool Map::is_safe() const {
    return _is_safe;
}

void Map::update(uint64_t delta_t) {
    while (!actions.empty()) {
        entity_action_t ent_act = actions.front();
        actions.pop();
        ent_act.action->execute(*this, ent_act.entity);
        delete ent_act.action;
    }
    EntityMatrix copy = entity_matrix;
    for (auto& it : copy) {
        it.second->update(delta_t);
    }
    monster_spawner.update(delta_t);
}

void Map::push_log(const map_log_t& log) {
    update_logs.push(log);
}

void Map::push_action(EntityId entity_id, Action* action) {
    actions.push({entity_id, action});
}

std::queue<map_log_t>& Map::get_update_logs() {
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

bool Map::dirty_entities() const {
    return _dirty_entities;
}
nlohmann::json Map::get_entity_data() {
    nlohmann::json entities;
    entities = nlohmann::json::array();
    for (auto& it : entity_matrix) {
        entities.push_back(it.second->get_data());
    }
    _dirty_entities = false;
    return entities;
}

bool Map::dirty_loot() const {
    return _dirty_loot;
}
nlohmann::json Map::get_loot_data() {
    nlohmann::json drops;
    drops = nlohmann::json::array();
    for (auto& it : loot_matrix) {
        drops.push_back(
            {{"pos", it.first}, {"item_info", it.second->get_data()}});
    }
    _dirty_loot = false;
    return drops;
}

nlohmann::json Map::get_map_data() {
    return visual_map_info;
}

position_t Map::get_nearest_entity_pos(position_t entity_pos,
                                       unsigned int max_distance,
                                       entity_type_t entity_type) {
    std::queue<position_t> queue;
    std::unordered_set<position_t, PositionHasher, PositionComparator> visited;
    queue.push(entity_pos);
    while (!queue.empty()) {
        position_t p = queue.front();
        queue.pop();
        if (visited.count(p))
            continue;
        visited.emplace(p);
        position_t aux[4] = {
            {p.x + 1, p.y}, {p.x, p.y + 1}, {p.x - 1, p.y}, {p.x, p.y - 1}};
        for (position_t it : aux) {
            unsigned int distance =
                std::abs(it.x - entity_pos.x) + std::abs(it.y - entity_pos.y);
            if (distance > max_distance)
                continue;
            if (!entity_matrix.count(it)) {
                queue.push(it);
                continue;
            }
            Entity* entity = entity_matrix.at(it);
            if (entity->get_type() == entity_type && entity->is_alive()) {
                return position_map.at(entity->get_id());
            }
        }
    }
    return entity_pos;
}

void Map::drop_loot(EntityId entity_id, Item* item) {
    _dirty_loot = true;
    position_t entity_pos = position_map.at(entity_id);
    position_t item_pos = get_nearest_free_position(loot_matrix, entity_pos);
    loot_matrix.emplace(item_pos, item);
}

void Map::drop_loot(EntityId entity_id, const std::vector<Item*>& drops) {
    for (auto it : drops) drop_loot(entity_id, it);
}

Item* Map::pickup_loot(EntityId entity_id) {
    position_t position = position_map.at(entity_id);
    if (!loot_matrix.count(position))
        return nullptr;
    _dirty_loot = true;
    Item* item = loot_matrix.at(position);
    loot_matrix.erase(position);
    return item;
}
