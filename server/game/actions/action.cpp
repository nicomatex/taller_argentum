#include "action.h"

#include "../map.h"

Entity* Action::get_entity(Map& map, EntityId entity_id) {
    if (!map.entity_map.count(entity_id))
        return nullptr;
    return map.entity_map.at(entity_id);
}

Entity* Action::get_entity(Map& map, position_t position) {
    if (!map.entity_matrix.count(position))
        return nullptr;
    return map.entity_matrix.at(position);
}

Action::~Action() {}
