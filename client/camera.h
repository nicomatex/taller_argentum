#ifndef __CAMERA_H
#define __CAMERA_H

#include <vector>

#include "visual_component.h"
#include "include/SDL/sdl_area.h"

class Camera {
   private:
    /* Ancho que se va a renderizar en tiles. */
    int width_tiles;

    /* Altura que se va a renderizar en tiles. */
    int height_tiles;

    /* Coordenadas del tile donde esta centrada la camara. */
    int x_center_tile;
    int y_center_tile;
    
    const VisualComponent &follow_component;

    /* Devuelve true si un componente visual esta dentro del campo
    de vision de la camara.*/
    bool _is_within_visual_range(VisualComponent *component);

    /* Devuelve el area fisica donde deberia ser dibujado el componente.*/
    SDLArea _get_render_area(VisualComponent *component);

    /* Actualiza la posicion de la camara segun el objeto que esta siguiendo. */
    void _update_position();

    /* Indica si la camara esta pegada contra una esquina */
    bool _is_locked_x;
    bool _is_locked_y;
   public:
    Camera(const VisualComponent &follow_component);
    ~Camera();

    /* Renderiza los componentes que esten en el campo de vision de la camara.*/
    void render_components(std::vector<VisualComponent *> components);

    
    void render_map();  // todo
};

#endif
