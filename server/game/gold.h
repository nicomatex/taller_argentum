#ifndef GOLD_H
#define GOLD_H

#include "item.h"

class Gold : public Item {
   public:
   	Gold();
   	Gold(item_info_t item_info, uint32_t stack = 0);
   	~Gold();
};

#endif // GOLD_H