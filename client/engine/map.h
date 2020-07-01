#ifndef __MAP_H
#define __MAP_H
#include <vector>

#include "../../include/nlohmann/json.hpp"
#include "decoration.h"
#include "renderizable_object.h"

using json = nlohmann::json;

class Map {
   private:
    int height;
    int width;
    std::vector<std::vector<Decoration>> background_layers;
    std::vector<std::vector<Decoration>> foreground_layers;

    bool is_valid;

   public:
    Map(json map_description);
    Map();
    void generate(json map_description);
    ~Map();
    int get_width();
    int get_height();

    /* Devuelve una referencia a los componentes visuales en la n-esima capa del
     * mapa. */
    std::vector<std::vector<Decoration>>& get_background_layers();
    
    std::vector<std::vector<Decoration>>& get_foreground_layers();
};

#endif