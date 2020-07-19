#ifndef MERCHANT_H
#define MERCHANT_H

#include "../items/item_container.h"
#include "npc.h"
#include "player.h"

#define MERCH_SLOTS_INV 10

class Merchant : public Npc {
   private:
    ItemContainer inventory;

   public:
    Merchant(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Merchant();
    /**
     * @brief Vende el item del inventario del player que se encuentra en el
     * SlotId slot, en caso de no haber, no hace nada. Si el inventario del
     * comerciante no se encuentra lleno, se agregara el oro correspondiente por
     * la venta al player (el oro proviene de la billetera del npc), y el item
     * sera removido del inventario del player. Si el inventario del comerciante
     * se encuentra lleno, la venta no se produce.
     *
     *
     * @param slot
     * @param stack
     * @param player
     */
    void sell(SlotId slot, uint32_t stack, Player* player);
    /**
     * @brief Compra del item del inventario del npc que se encuentra en el
     * SlotID slot, en caso de no haber, no hace nada. El item será removido del
     * inventario del comerciante, y se incremetara la billetera del npc en la
     * cantidad correspondiente. Se removera del la billetera del player el oro
     * correspondiente, y se agregara el item a su inventario.
     *
     * @param slot
     * @param stack
     * @param player
     */
    void buy(SlotId slot, uint32_t stack, Player* player);
    /**
     * @brief Devuelve un string que representa la lista de los items que tiene el
     * comerciante para vender, detallando precio y stock.
     *
     * @return const std::string
     */
    const std::string list_sale() const;
};

#endif  // MERCHANT_H