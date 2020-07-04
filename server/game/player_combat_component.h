#ifndef PLAYER_COMBAT_COMPONENT_H
#define PLAYER_COMBAT_COMPONENT_H

#include "combat_component.h"
#include "items/armor.h"
#include "items/weapon.h"

class PlayerCombatComponent : public CombatComponent {
   private:
    Armor* helmet;
    Armor* armor;
    Armor* shield;
    Weapon* weapon;

    float attack_speed;
    unsigned int attack_accumulator;

   public:
    PlayerCombatComponent(ItemId helmet_id, ItemId armor_id, ItemId shield_id,
                          ItemId weapon_id, unsigned int max_hp,
                          unsigned int max_mp, unsigned int current_hp,
                          unsigned int current_mp, float attack_speed);
    ~PlayerCombatComponent();

    // int special();
    virtual damage_t attack() override;
    virtual attack_result_t receive_damage(damage_t raw_damage) override;

    Armor* equip(Armor* armor);
    Weapon* equip(Weapon* weapon);

    void update(uint64_t delta_t) override;
    bool attack_ready() const override;

    nlohmann::json get_data() const override;
    nlohmann::json get_persist_data() const;
};

#endif  // PLAYER_COMBAT_COMPONENT_H
