#include "npc.h"

#include "components/npc_movement_component.h"
#include "components/npc_combat_component.h"

Npc::Npc(EntityId entity_id, nlohmann::json npc_info, Map& map)
    : Entity(entity_id, npc_info["name"],
             new NpcMovementComponent(1, map, entity_id),
             new NpcCombatComponent(), 1, 0),
      map(map),
      sprite_id(npc_info["sprite_id"]),
      proffesion(npc_info["profession"]) {}

Npc::~Npc() {}

entity_type_t Npc::get_type() const {
    return NPC;
}

void Npc::die() {}

bool Npc::is_alive() const {
    return false;
}

nlohmann::json Npc::get_data() const {
    nlohmann::json entity_data;
    entity_data["entity_id"] = get_id();
    entity_data["type_id"] = get_type();
    entity_data["name"] = get_name();
    entity_data["sprite_id"] = sprite_id;
    nlohmann::json aux = movement_component->get_data();
    for (auto& it : aux.items()) {
        entity_data[it.key()] = it.value();
    }
    return entity_data;
}

void Npc::update(uint64_t delta_t) {}

npc_proffesion_t Npc::get_profession() {
    return proffesion;
}