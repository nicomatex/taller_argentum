#include "armor.h"

#include "../random_event_generator.h"

Armor::Armor() {}

Armor::Armor(item_info_t item_info, armor_info_t armor_info, uint32_t stack)
    : Item(item_info, stack), armor_info(armor_info) {}

Armor::~Armor() {}

int Armor::reduce_damage(int damage) {
    return damage - (int)RandomEventGenerator::random_in(
                        armor_info.min_defense, armor_info.max_defense);
}

nlohmann::json Armor::get_data() const {
    nlohmann::json info = Item::get_data();
    info["armor_info"] = armor_info;
    return info;
}

slot_info_t Armor::get_slot() const {
    return armor_info.slot_info;
}
