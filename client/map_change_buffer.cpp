#include "map_change_buffer.h"

MapChangeBuffer::MapChangeBuffer()
    : map_info_ready(false), entity_info_ready(false) {}

MapChangeBuffer::~MapChangeBuffer(){}

void MapChangeBuffer::wait_for_map() {
    std::unique_lock<std::mutex> l(m);
    while (!map_info_ready || !entity_info_ready) {
        cv.wait(l);
    }
}

void MapChangeBuffer::set_map_info(nlohmann::json new_map_info) {
    map_info = new_map_info;
    map_info_ready = true;
    cv.notify_all();
}

void MapChangeBuffer::set_follow_entity_id(unsigned int new_follow_entity_id) {
    follow_entity_id = new_follow_entity_id;
    entity_info_ready = true;
    cv.notify_all();
}

nlohmann::json MapChangeBuffer::get_map_info() { return map_info; }

int MapChangeBuffer::get_follow_entity_id() { return follow_entity_id; }

void MapChangeBuffer::reset() {
    map_info_ready = false;
    entity_info_ready = false;
}