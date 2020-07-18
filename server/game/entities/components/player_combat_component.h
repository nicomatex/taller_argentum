#ifndef PLAYER_COMBAT_COMPONENT_H
#define PLAYER_COMBAT_COMPONENT_H

#include <vector>

#include "../../attribute_manager.h"
#include "../../items/armor.h"
#include "../../map_log_factory.h"
#include "../player.h"
#include "combat_component.h"

class Weapon;

class PlayerCombatComponent : public CombatComponent {
   private:
    Player& player;
    stats_t stats;
    float attack_speed;
    unsigned int attack_accumulator;
    unsigned int regen_counter;
    Armor* helmet;
    Armor* armor;
    Armor* shield;
    Weapon* weapon;
    bool is_meditating;
    unsigned int meditate_counter;
    bool is_resuscitating;
    int resuscitate_counter;

   public:
    PlayerCombatComponent(ItemId helmet_id, ItemId armor_id, ItemId shield_id,
                          ItemId weapon_id, unsigned int current_hp,
                          unsigned int current_mp, stats_t stats,
                          Player& player, float attack_speed);
    ~PlayerCombatComponent();

    std::vector<map_log_t> use_ability(Entity* target, position_t source,
                                       position_t dest);
    attack_t attack() override;
    attack_result_t receive_damage(attack_t attack) override;

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
    void set_meditate(bool meditating);
    void resuscitate(int delta_t);

    void update(uint64_t delta_t) override;
    bool attack_ready() const override;

    nlohmann::json get_data() const override;
    nlohmann::json get_persist_data() const;
};

#endif  // PLAYER_COMBAT_COMPONENT_H
