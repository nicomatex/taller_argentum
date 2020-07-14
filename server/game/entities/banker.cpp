#include "banker.h"

#include <sstream>
#include "../bank.h"

Banker::Banker(EntityId entity_id, nlohmann::json npc_info, Map &map)
    : Npc(entity_id, npc_info, map) {}

Banker::~Banker() {}

const std::string Banker::list_vault(std::string player_name) const {
    std::stringstream ss;
    std::string greeting =
        "Bienvenido al banco de Gringotts, usted tiene en su cuenta:";
    ss << greeting;
    ss << "    ";
    ss << "[ORO]" << "   ";

    SlotId slot_id = 0;
    unsigned int counter = 0;
    nlohmann::json json_vault = Bank::get_vault_data(player_name);
    ss << json_vault["curr_gold"] << "\n";
    for (auto& item : json_vault["items"]) {
        if (item["type"] != 0) {
            ss << "[" << std::to_string(slot_id) << "]"
               << " ";
            ss << "Nombre: " << item["name"] << ", ";
            ss << "cantidad: " << item["actual_stack"] << "               ";
            counter++;
            if (counter == 2) {
                ss << "\n";
                counter = 0;
            }   
        }
        slot_id++;
    }
    std::string msg = ss.str();
    return msg;
}

void Banker::deposit_gold(uint32_t amount, Player *player) {
    Bank::deposit_gold(amount, player);
}

void Banker::withdraw_gold(uint32_t amount, Player *player) {
    Bank::withdraw_gold(amount, player);
}

void Banker::deposit_item(SlotId slot, uint32_t amount, Player *player) {
    Bank::deposit_item(slot, amount, player);
}

void Banker::withdraw_item(SlotId slot, uint32_t amount, Player *player) {
    Bank::withdraw_item(slot, amount, player);       
}


