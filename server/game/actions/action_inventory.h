#ifndef ACTION_INVENTORY_H
#define ACTION_INVENTORY_H

#include "../items/item_container.h"
#include "action.h"

class ActionInventory : public Action {
   private:
    SlotId slot;

   public:
    ActionInventory(SlotId slot);

    void execute(Map& map, EntityId entity_id) const override;
};

#endif  // ACTION_INVENTORY_H
