#ifndef WEAPON_H
#define WEAPON_H

#include "item.h"

typedef struct weapon_info {
    uint16_t min_damage;
    uint16_t max_damage;
    float attack_speed;
} weapon_info_t;

inline void to_json(nlohmann::json& j, const weapon_info_t& w) {
    j["min_damage"] = w.min_damage;
    j["max_damage"] = w.max_damage;
    j["attack_speed"] = w.attack_speed;
}

inline void from_json(const nlohmann::json& j, weapon_info_t& w) {
    j["min_damage"].get_to(w.min_damage);
    j["max_damage"].get_to(w.max_damage);
    j["attack_speed"].get_to(w.attack_speed);
}

class Weapon : public Item {
   private:
    weapon_info_t weapon_info;

   public:
    Weapon();
    Weapon(item_info_t item_info, weapon_info_t weapon_info,
           uint32_t stack = 0);

    /**
     * @brief Devuelve un valor en el rango de daño del arma.
     *
     * El cálculo de daño para un arma es un valor aleatorio entre el mínimo y
     * máximo daño posible por la misma.
     *
     * @return int Daño en puntos de vida.
     */
    int deal_damage();

    /**
     * @brief Devuelve el valor de la velocidad de ataque del arma.
     *
     * @return float Valor en ataques/seg.
     */
    float get_attack_speed();

    nlohmann::json get_data() const override;
    ~Weapon();
};

#endif  // WEAPON_H