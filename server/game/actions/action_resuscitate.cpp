#include "action_resuscitate.h"

#include "../entities/healer.h"
#include "../entities/player.h"

#include <iostream> //Temp

ActionResuscitate::ActionResuscitate() {}

void ActionResuscitate::execute(Map& map, EntityId entity_id) const {
    // Por ahora la posicion esta hardcodeada
    Healer* healer = static_cast<Healer*>(Action::get_entity(map, position_t{20,19}));
    if (!healer || healer->get_type() != NPC || healer->get_profession() != HEALER) {
        std::cerr << "No hay un cura en esa posicion!" << std::endl;
        return;
    }
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || player->is_alive())
        return;
    healer->resuscitate(player);
}
