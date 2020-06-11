#ifndef __MAP_H
#define __MAP_H
#include <vector>
#include "renderizable_object.h"
#include "decoration.h"

class Map {
   private:
    int height;
    int width;
    std::vector<std::vector<Decoration>> visual_layers;
    
   public:
    Map(const std::string &map_file, SDLTexture &tileset);
    ~Map();

    /* Devuelve una referencia a los componentes visuales en la n-esima capa del mapa. */
    std::vector<Decoration>& get_layer(int n);
};

#endif