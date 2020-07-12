#ifndef MERCHANT_H
#define MERCHANT_H

#include "npc.h"
#include "../items/item_container.h"
#include "player.h"

#define MERCH_SLOTS_INV 10

class Merchant : public Npc {
   private:
    ItemContainer inventory;
   public:
    Merchant(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Merchant();
    Gold* sell(Item *item, uint32_t stack);
    void buy(SlotId slot, uint32_t stack, Player* player);
    const std::string list_sale() const;
};

#endif // MERCHANT_H