#ifndef __STATS_COMPONENT_H
#define __STATS_COMPONENT_H

#include <mutex>
#include <unordered_map>

#include "../../../include/nlohmann/json.hpp"
#include "../ECS/component.h"

typedef std::unordered_map<std::string, unsigned int> StatValues;

class StatsComponent : public Component {
   private:
    StatValues max_stat_values;
    StatValues current_stat_values;
    int level;

    std::recursive_mutex m;

   public:
    /**
     * @brief Crea un objeto StatsComponent
     *
     * @param max_hp Vida maxima.
     * @param current_hp Vida actual.
     * @param max_mp Mana maxima.
     * @param current_mp Mana actual.
     * @param max_xp Experiencia maxima.
     * @param current_xp Experiencia actual.
     * @param level Nivel.
     */
    StatsComponent(int max_hp, int current_hp, int max_mp, int current_mp,
                   int max_xp, int current_xp, int level);

    /**
     * @brief Devuelve el valor actual de un stat
     *
     * @param stat_name Nombre del stat. Puede ser "hp", "mp" o "xp".
     * @return unsigned int
     */
    unsigned int get_stat_current_value(const std::string &stat_name);

    /**
     * @brief Devuelve el valor maximo de un stat.
     *
     * @param stat_name Nombre del stat. Puede ser "hp", "mp" o "xp".
     * @return unsigned int
     */
    unsigned int get_stat_max_value(const std::string &stat_name);

    /**
     * @brief Setea el valor actual de un stat.
     *
     * @param stat_name Nombre del stat. Puede ser "hp", "mp" o "xp".
     * @param new_value Nuevo valor actual del stat.
     */
    void set_stat_current_value(const std::string &stat_name,
                                unsigned int new_value);

    /**
     * @brief Set the stat max value object
     *
     * @param stat_name Nombre del stat. Puede ser "hp", "mp" o "xp".
     * @param new_value Nuevo valor maximo del stat.
     */
    void set_stat_max_value(const std::string &stat_name,
                            unsigned int new_value);

    /**
     * @brief Devuelve el nivel.
     *
     * @return int
     */
    int get_level();

    /**
     * @brief Setea el nivel.
     *
     * @param new_level Nuevo nivel.
     */
    void set_level(int new_level);

    /**
     * @brief Actualiza la componente segun la informacion de actualizacion del
     * servidor.
     *
     * @param entity_info json con la informacion de actualizacion del servidor.
     */
    void server_update(nlohmann::json entity_info);
    void init() override;
    void update() override;
};

#endif