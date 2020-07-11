#ifndef PLAYER_COMBAT_COMPONENT_H
#define PLAYER_COMBAT_COMPONENT_H

#include "../../../attribute_manager.h"
#include "../../items/armor.h"
#include "../../items/weapon.h"
#include "../player.h"
#include "combat_component.h"

class PlayerCombatComponent : public CombatComponent {
   private:
    Player& player;
    Armor* helmet;
    Armor* armor;
    Armor* shield;
    Weapon* weapon;
    stats_t stats;
    float attack_speed;
    unsigned int attack_accumulator;
    unsigned int regen_counter;

   public:
    PlayerCombatComponent(ItemId helmet_id, ItemId armor_id, ItemId shield_id,
                          ItemId weapon_id, unsigned int current_hp,
                          unsigned int current_mp, stats_t stats,
                          Player& player, float attack_speed);
    ~PlayerCombatComponent();

    // int special();
    virtual attack_t attack() override;
    virtual attack_result_t receive_damage(attack_t attack) override;

    Armor* equip(Armor* armor);
    Weapon* equip(Weapon* weapon);
    Armor* unequip_helmet();
    Armor* unequip_chest();
    Armor* unequip_shield();
    Weapon* unequip_weapon();

    void regen_max();
    void regen(unsigned int amount_hp, unsigned int amount_mp);
    void regen_hp(unsigned int amount_hp);
    void regen_mp(unsigned int amount_mp);

    void update(uint64_t delta_t) override;
    bool attack_ready() const override;

    nlohmann::json get_data() const override;
    nlohmann::json get_persist_data() const;
};

#endif  // PLAYER_COMBAT_COMPONENT_H
