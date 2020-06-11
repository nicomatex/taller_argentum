#ifndef __RENDERIZABLE_OBJECT_H
#define __RENDERIZABLE_OBJECT_H

/* Interfaz que deben implementar todos los objetos que vayan
a ser renderizados por pantalla. */
#include <mutex>

#include "animation_pack.h"
#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_area.h"
#include "SDL/sdl_timer.h"

/* Interfaz que deben implementar todos los componentes
que vayan a ser renderizados por la camara.*/
class RenderizableObject {
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
    RenderizableObject(int x, int y, int width, int height,int x_offset, int y_offset);
    virtual ~RenderizableObject(){}

    /* Renderiza el objeto en pantalla. */
    virtual void render(const SDLArea &dest) = 0;

    /* Establece la nueva posicion. */
    void set_position(int new_x, int new_y);

    /* Devuelve el ancho en tiles del objeto. */
    int get_width() const;

    /* Devuelve la altura en tiles del objeto. */
    int get_height() const;

    /* Devuelve true si el actor esta en medio de un movimiento.*/
    virtual bool is_transitioning() const;

    virtual int get_x() const;
    virtual int get_y() const;

    /* Devuelve el offset total de renderizacion en centesimas de tile. */
    virtual int get_x_offset() const;
    virtual int get_y_offset() const;

    /* Devuelve el ofset de transicion en centesimas de tile. */
    virtual int get_transition_offset_x() const;
    virtual int get_transition_offset_y() const;

    /* Debe ser llamado luego de renderizar para actualizar el estado de las constantes 
    visuales.*/
    virtual void update();
};

#endif
