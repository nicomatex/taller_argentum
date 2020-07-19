#ifndef BANKER_H
#define BANKER_H

#include "npc.h"
#include "player.h"

class Banker : public Npc {
   public:
    Banker(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Banker();
    /**
     * @brief Lista la boveda asociada al jugador.
     * 
     * @param player_name 
     * @return const std::string 
     */
    const std::string list_vault(std::string player_name) const;
    void deposit_gold(uint32_t amount, Player *player);
    void withdraw_gold(uint32_t amount, Player *player);
    void deposit_item(SlotId slot, uint32_t amount, Player *player);
    void withdraw_item(SlotId slot, uint32_t amount, Player *player);
};

#endif // BANKER_H