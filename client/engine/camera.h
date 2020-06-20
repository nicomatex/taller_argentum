#ifndef __CAMERA_H
#define __CAMERA_H

#include <vector>

#include "SDL/sdl_timer.h"
#include "components/position_component.h"
#include "decoration.h"
#include "renderizable_object.h"

class Camera {
   private:
    /* Ancho que se va a renderizar en tiles. */
    int width_tiles;

    /* Altura que se va a renderizar en tiles. */
    int height_tiles;

    /* Coordenadas del tile donde esta centrada la camara. */
    int x_center_tile;
    int y_center_tile;

    int camera_offset_x;
    int camera_offset_y;

    SDLTimer movement_timer;

    int map_size; /* Lado del mapa, en tiles (los mapas son cuadrados). */

    int tile_size; /* Lado de cada tile, en pixeles.*/

    int speed;  // En tiles/segundo.

    const PositionComponent &follow_component;

    /* Devuelve true si un componente visual esta dentro del campo
    de vision de la camara.*/
    bool _is_within_visual_range(RenderizableObject *component);

    /* Devuelve el area fisica donde deberia ser dibujado el componente.*/
    SDL_Rect _get_render_area(RenderizableObject *component, int x, int y,
                              int x_tmp_offset, int y_tmp_offset);
    SDL_Rect _get_render_area(Decoration &decoration);

    void _update_offset();

   public:
    Camera(const PositionComponent &follow_component, int map_size,
           int tile_size, int viewport_width, int viewport_height, int speed);
    ~Camera();

    /* Actualiza la posicion de la camara segun el objeto que esta siguiendo. */
    void update();

    void draw(RenderizableObject *component, int x, int y, int x_tmp_offset,
              int y_tmp_offset);

    /* Renderiza todos las entidades con una componente visual.*/
    void draw_all();
    
    void render_map_layer(std::vector<Decoration> &layer);
};

#endif
