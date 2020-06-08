#ifndef __VISUAL_COMPONENT_H
#define __VISUAL_COMPONENT_H

/* Interfaz que deben implementar todos los objetos que vayan
a ser renderizados por pantalla. */
#include <mutex>

#include "animation_pack.h"
#include "include/SDL/sdl_animated_sprite.h"
#include "include/SDL/sdl_area.h"
#include "include/SDL/sdl_timer.h"

/* Interfaz que deben implementar todos los componentes
que vayan a ser renderizados por la camara.*/
class VisualComponent {
   protected:
    int x;
    int y;

    int height;
    int width;

    /* Estos offset estan medidos en centesimas de tile (es decir, 100 = 1
     * tile). Se usan para que la transicion sea smooth.*/

    int x_offset;
    int y_offset;

   public:
    VisualComponent(int x, int y, int width, int height,int x_offset, int y_offset);
    virtual ~VisualComponent(){}

    /* Renderiza el objeto en pantalla. */
    virtual void render(const SDLArea &dest) = 0;

    /* Establece la nueva posicion. */
    void set_position(int new_x, int new_y);

    /* Devuelve el ancho en tiles del objeto. */
    int get_width() const;

    /* Devuelve la altura en tiles del objeto. */
    int get_height() const;

    /* Devuelve el tile absoluto donde esta parado el objeto. */
    int get_x() const;
    int get_y() const;

    /* Devuelve true si el actor esta en medio de un movimiento.*/
    virtual bool is_transitioning() const;


    /* Devuelve el offset de renderizacion en centesimas de tile. */
    virtual int get_x_offset() const;
    virtual int get_y_offset() const;

    /* Debe ser llamado luego de renderizar para actualizar el estado de las constantes 
    visuales.*/
    virtual void update();
};

#endif
