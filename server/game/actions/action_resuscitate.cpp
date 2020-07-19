#include "action_resuscitate.h"

#include <iostream>  //Temp

#include "../entities/healer.h"
#include "../entities/player.h"

ActionResuscitate::ActionResuscitate() {}

void ActionResuscitate::execute(Map& map, EntityId entity_id) const {
    // Por ahora la posicion esta hardcodeada
    Healer* healer =
        static_cast<Healer*>(Action::get_entity(map, map.get_healer_pos()));
    if (!healer || healer->get_type() != NPC ||
        healer->get_profession() != HEALER) {
        std::cerr << "No hay un cura en esa posicion!" << std::endl;
        return;
    }
    Player* player = static_cast<Player*>(Action::get_entity(map, entity_id));
    if (!player || player->is_alive())
        return;
    healer->resuscitate(player);
    map.push_log(MapLogFactory::message(
                player->get_name(), {{"message", "Usted sera resucitado en breve!"},
                                     {"from", healer->get_name()}}));
}
