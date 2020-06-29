#include "map_transitions.h"

// Temp
#include <iostream>

MapTransitions::MapTransitions(nlohmann::json changes, int width, int height) {
    for (auto& it : changes["teleports"].items()) {
        nlohmann::json& teleport = it.value();
        position_t position = it.value()["position"];
        position_t pos_dest = it.value()["destination"];
        MapId map_dest = it.value()["destination"]["map_id"];
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

bool MapTransitions::is_transition(position_t position) {
    return teleports.count(position);
}

void MapTransitions::push_change(std::string name, position_t position) {
    if (!teleports.count(position))
        return;
    auto dest_pair = teleports.at(position);
    map_change_t change = {name, dest_pair.first, dest_pair.second};
    changes_queue.push(change);
}

std::queue<map_change_t>& MapTransitions::get_changes() {
    return changes_queue;
}
