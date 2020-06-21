#include "map_change_buffer.h"

MapChangeBuffer::MapChangeBuffer() : ready(false) {}

MapChangeBuffer::~MapChangeBuffer() {}

void MapChangeBuffer::wait_for_map() {
    std::unique_lock<std::mutex> l(m);
    while (!ready) {
        cv.wait(l);
    }
}

void MapChangeBuffer::fill(nlohmann::json new_map_info,
                           unsigned int new_follow_entity_id) {
    map_info = new_map_info;
    follow_entity_id = new_follow_entity_id;
    ready = true;
    cv.notify_all();
}

nlohmann::json MapChangeBuffer::get_map_info() { return map_info; }

int MapChangeBuffer::get_follow_entity_id() { return follow_entity_id; }

void MapChangeBuffer::reset() {
    ready = false;
}