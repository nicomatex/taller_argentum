#include "map_transitions.h"

// Temp
#include <iostream>

MapTransitions::MapTransitions(MapId map_id, nlohmann::json changes, int width,
                               int height) : map_id(map_id) {
    for (auto& it : changes["teleports"].items()) {
        nlohmann::json& teleport = it.value();
        position_t position = teleport["position"];
        position_t pos_dest = teleport["destination"]["pos"];
        MapId map_dest = teleport["destination"]["map_id"];
        teleports[position] = std::make_pair(map_dest, pos_dest);
    }
    if (changes["upper"] >= 0) {
        for (int i = 0; i < width; i++) {
            position_t dest = {i, height - 1};
            teleports[{i, -1}] = std::make_pair(changes["upper"], dest);
        }
    }
    if (changes["lower"] >= 0) {
        for (int i = 0; i < width; i++) {
            position_t dest = {i, 0};
            teleports[{i, height}] = std::make_pair(changes["lower"], dest);
        }
    }
    if (changes["right"] >= 0) {
        for (int i = 0; i < height; i++) {
            position_t dest = {0, i};
            teleports[{width, i}] = std::make_pair(changes["right"], dest);
        }
    }
    if (changes["left"] >= 0) {
        for (int i = 0; i < height; i++) {
            position_t dest = {width - 1, i};
            teleports[{-1, i}] = std::make_pair(changes["left"], dest);
        }
    }
}
MapTransitions::~MapTransitions() {}

void MapTransitions::push_if_transition(std::string name, position_t position) {
    if (!teleports.count(position))
        return;
    auto dest_pair = teleports.at(position);
    map_change_t change = {name, dest_pair.first, dest_pair.second};
    changes_queue.push(change);
}

std::queue<map_change_t>& MapTransitions::get_changes() {
    return changes_queue;
}

void MapTransitions::teleport(std::string name, position_t dest) {
    map_change_t change = {name, map_id, dest};
    changes_queue.push(change);
}
