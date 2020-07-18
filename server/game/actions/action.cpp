#include "action.h"

#include "../map.h"

Entity* Action::get_entity(Map& map, EntityId entity_id) {
    if (!map.position_map.count(entity_id))
        return nullptr;
    return map.entity_matrix.at(map.position_map.at(entity_id));
}

Entity* Action::get_entity(Map& map, position_t position) {
    if (!map.entity_matrix.count(position))
        return nullptr;
    return map.entity_matrix.at(position);
}

void Action::rm_entity(Map& map, EntityId entity_id) {
    map.rm_entity(entity_id);
}

Action::~Action() {}
