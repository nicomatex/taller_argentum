#include "npc.h"

Npc::Npc() {}

Npc::~Npc() {}

entity_type_t Npc::get_type() {
	return NPC;
}

void Npc::update(unsigned int delta_t) {
	//TODO: Pensar como es el update.
}