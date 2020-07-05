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
    /*
        Devuelve la experiencia necesaria para pasar al siguiente nivel.
    */
    int exp_to_next_level(unsigned int current_level, unsigned int current_exp);

   public:
    ExperienceComponent(unsigned int level = 1, unsigned int exp = 0);
    ~ExperienceComponent();
    /*
        Agrega "exp" a la experencia actual, actualizando los niveles.
    */
    void add_exp(int exp);
    /*
        Reduce la experiencia actual en un X% sobre la diferencia entre
        la experiencia base del nivel actual, y la experiencia actual
        (se puede obtener la experiencia base pidiendo el limite del nivel
        anterior)
        En ningun momento puede bajar de nivel el personaje.
    */
    void reduce();
    /*
        Devuelve el limite de experiencia asociado al nivel (se entiende
        por limite de experiencia, a aquel valor para el cual se produce
        un aumento de nivel al igualarlo/superarlo)
    */
    int get_xp_limit_level(unsigned int level) const;
    unsigned int get_level() const;
    void set_level(unsigned int level);
    nlohmann::json get_data() const;
    nlohmann::json get_persist_data() const;
};

#endif  // EXPERIENCE_COMPONENT_H