#ifndef __VISUAL_COMPONENT_H
#define __VISUAL_COMPONENT_H

/* Interfaz que deben implementar todos los objetos que vayan
a ser renderizados por pantalla. */
#include <mutex>

#include "animation_pack.h"
#include "include/SDL/sdl_animated_sprite.h"
#include "include/SDL/sdl_area.h"
#include "include/SDL/sdl_timer.h"

class VisualComponent {
   private:
    AnimationPack animation_pack;
    Orientation orientation;
    MovementStatus movement_status;
    SDLTimer timer;

    int x_tile;
    int y_tile;

    int height_tile;
    int width_tile;

    /* Estos offset estan medidos en decimas de tile (es decir, 10 = 1
     * tile). Se usan para que la transicion sea smooth.*/
    int x_offset;
    int y_offset;

    void _update_offset();
    
   public:
    VisualComponent(AnimationPack &&animation_pack, int x_tile, int y_tile,
                    int width_tile, int height_tile);
    /* Renderiza el objeto en pantalla. */
    void render(const SDLArea &dest);

    /* Devuelve el ancho en tiles del objeto. */
    int get_width_tile() const;

    /* Devuelve la altura en tiles del objeto. */
    int get_height_tile() const;

    /* Devuelve el tile absoluto donde esta parado el objeto. */
    int get_x_tile() const;
    int get_y_tile() const;

    /* Establece la nueva posicion del componente. */
    void set_position(int new_x_tile, int new_y_tile);

    /* Establece la nueva orientacion del componente.*/
    void set_orientation(Orientation new_orientation);

    /* Establece el nuevo estado de movimiento*/
    void set_move_status(MovementStatus new_movement_status);

    /* Devuelve el offset de renderizacion en decimas de tile. */
    int get_x_offset() const;
    int get_y_offset() const;
};

#endif