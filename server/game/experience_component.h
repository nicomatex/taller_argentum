#ifndef EXPERIENCE_COMPONENT_H
#define EXPERIENCE_COMPONENT_H

#include "../../include/nlohmann/json.hpp"

// Limite = int(1000 * Nivel^1.8)
#define EXP_MULT 1000
#define EXP_EXPO 1.8
// Porcentaje sobre lo minimo del nivel, que pierde de experiencia al
// morir
#define EXP_REDU 10

class ExperienceComponent {
   private:
    unsigned int current_level;
    unsigned int current_exp;
    int exp_to_next_level(unsigned int current_level, unsigned int current_exp);

   public:
    ExperienceComponent(unsigned int level = 1, unsigned int exp = 0);
    ~ExperienceComponent();
    void add_exp(int exp);
    void reduce();
    int get_xp_limit_level(unsigned int level) const;
    unsigned int get_level();
    void set_level(unsigned int level);
    nlohmann::json get_data() const;
    nlohmann::json get_persist_data() const;
};

#endif  // EXPERIENCE_COMPONENT_H