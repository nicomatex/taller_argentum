#ifndef __CAMERA_H
#define __CAMERA_H

#include <vector>

#include "renderizable_object.h"
#include "decoration.h"
#include "SDL/sdl_area.h"

class Camera {
   private:
    /* Ancho que se va a renderizar en tiles. */
    int width_tiles;

    /* Altura que se va a renderizar en tiles. */
    int height_tiles;

    /* Coordenadas del tile donde esta centrada la camara. */
    int x_center_tile;
    int y_center_tile;
    
    int map_size; /* Lado del mapa, en tiles (los mapas son cuadrados). */

    int tile_size; /* Lado de cada tile, en pixeles.*/

    const RenderizableObject &follow_component;

    /* Devuelve true si un componente visual esta dentro del campo
    de vision de la camara.*/
    bool _is_within_visual_range(RenderizableObject *component);

    /* Devuelve el area fisica donde deberia ser dibujado el componente.*/
    SDLArea _get_render_area(RenderizableObject *component);

    /* Indica si la camara esta pegada contra una esquina */
    bool _is_locked_x;
    bool _is_locked_y;
   public:
    Camera(const RenderizableObject &follow_component,int map_size, int tile_size);
    ~Camera();

    /* Actualiza la posicion de la camara segun el objeto que esta siguiendo. */
    void update_position();

    /* Renderiza los componentes que esten en el campo de vision de la camara.*/
    void render_components(std::vector<RenderizableObject *> components);

    void draw(RenderizableObject *component);
    
    void render_map_layer(std::vector<Decoration> &layer);  // todo
};

#endif
