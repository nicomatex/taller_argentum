#ifndef __MAP_H
#define __MAP_H
#include <vector>
#include "renderizable_object.h"
#include "decoration.h"
#include "json.hpp"

using json = nlohmann::json;

class Map {
   private:
    int height;
    int width;
    std::vector<std::vector<Decoration>> visual_layers;
    bool is_valid;

   public:
    Map(json map_description);
    Map();
    void generate(json map_description);
    ~Map();

    /* Devuelve una referencia a los componentes visuales en la n-esima capa del mapa. */
    std::vector<Decoration>& get_layer(int n);
};

#endif