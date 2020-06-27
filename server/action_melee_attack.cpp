#include "action_melee_attack.h"

#include "map.h"
#include "position.h"

// Temp
#include "event_factory.h"
#include "server_manager.h"

ActionMeleeAttack::ActionMeleeAttack() {}
ActionMeleeAttack::~ActionMeleeAttack() {}

void ActionMeleeAttack::execute(EntityId entity_id, Map& map) const {
    Entity* attacker = Action::get_entity(map, entity_id);
    if (!attacker)  // || !attacker->is_alive() TODO
        return;
    position_t attacked_pos =
        attacker->get_facing_position(map.get_position(entity_id));
    Entity* attacked = Action::get_entity(map, attacked_pos);
    if (!attacked)  // || !attacked->is_alive() TODO
        return;
    // int damage = attacker->attack(attacked);
    Player* player = (Player*)attacker;
    ServerManager& sm = ServerManager::get_instance();
    sm.send_to(sm.get_client_by_name(player->get_name()),
               EventFactory::chat_message("Attacando!"));
}
