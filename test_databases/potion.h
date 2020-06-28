#ifndef POTION_H
#define POTION_H

#include "item.h"

typedef struct potion_info {
	short health_var;
	short mana_var;
} potion_info_t;

inline void to_json(nlohmann::json& j, const potion_info_t& p) {
	j["health_var"] = p.health_var;
    j["mana_var"] = p.mana_var;
}

inline void from_json(const nlohmann::json& j, potion_info_t& p) {
	j["health_var"].get_to(p.health_var);
    j["mana_var"].get_to(p.mana_var);
}

class Potion : public Item {
   private:
   	potion_info_t potion_info;
   public:
    Potion();
   	Potion(item_info_t item_info, potion_info_t potion_info, uint32_t count = 0);
    nlohmann::json get_info() override;
   	~Potion();
};

#endif // POTION_H