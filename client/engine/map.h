#ifndef __MAP_H
#define __MAP_H
#include <exception>
#include <vector>

#include "../../include/nlohmann/json.hpp"
#include "decoration.h"
#include "renderizable_object.h"

using json = nlohmann::json;

class MapError : public std::exception {
   private:
    char msg_error[256];

   public:
    explicit MapError(const char* msg) noexcept;
    const char* what() const noexcept;
    ~MapError() noexcept {}
};

/**
 * @brief Mapa. Contiene toda la informacion estatica del mapa, asi como
 * tambien el loot que esta tirado en el suelo.
 *
 */
class Map {
   private:
    int height;
    int width;
    std::vector<std::vector<Decoration>> background_layers;
    std::vector<std::vector<Decoration>> foreground_layers;
    int loot_layer_index;
    int spell_layer_index;
    bool is_valid;

   public:
    /**
     * @brief Crea un objeto Map
     *
     * @param map_description json de informacion del mapa, generado por TILED
     * con las modificaciones adecuadas (ver seccion de mapas de la
     * documentacion).
     */
    Map(json map_description);
    Map();

    /**
     * @brief Regenera el mapa.
     *
     * @param map_description json de informacion del mapa, generado por TILED
     * con las modificaciones adecuadas (ver seccion de mapas de la
     * documentacion).
     */
    void generate(json map_description);
    ~Map();

    /**
     * @brief Devuelve el ancho en tiles del mapa.
     *
     * @return int
     */
    int get_width();

    /**
     * @brief Devuelve el alto en tiles del mapa.
     *
     * @return int
     */
    int get_height();

    /**
     * @brief Actualiza la capa de loot del mapa.
     *
     * @param loot_info informacion de loot provista por el servidor.
     */
    void update_loot_layer(nlohmann::json loot_info);
    
    /**
     * @brief Actualiza la capa de hechizos lanzados del mapa.
     * 
     * @param spell_info Informacion de hechizos provista por el servidor.
     */
    void update_spell_layer(nlohmann::json spell_info);

    /**
     * @brief Devuelve las capas que deben ser renderizadas por detras de las
     * entidades.
     *
     * @return std::vector<std::vector<Decoration>>&
     */
    std::vector<std::vector<Decoration>>& get_background_layers();

    /**
     * @brief Devuelve las capas que deben ser renderizadas por delante
     * de las entidades.
     *
     * @return std::vector<std::vector<Decoration>>&
     */
    std::vector<std::vector<Decoration>>& get_foreground_layers();
};

#endif