#include "action.h"

#include "map.h"

Entity& Action::get_entity(Map& map, EntityId entity_id) {
    return *map.entity_map.at(entity_id);
}

Action::~Action() {}
