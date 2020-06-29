#ifndef __RENDERIZABLE_OBJECT_H
#define __RENDERIZABLE_OBJECT_H

/* Interfaz que deben implementar todos los objetos que vayan
a ser renderizados por pantalla. */
#include <mutex>

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_timer.h"

typedef struct part_visual_info {
    int width;
    int height;
    int offset_x;
    int offset_y;
} visual_info_t;

/* Interfaz que deben implementar todos los componentes
que vayan a ser renderizados por la camara.*/
class RenderizableObject {
   protected:
    visual_info_t visual_info;

   public:
    RenderizableObject(visual_info_t visual_info);
    virtual ~RenderizableObject() {}

    /* Renderiza el objeto en pantalla. */
    virtual void render(SDL_Rect dest) = 0;

    /* Devuelve el ancho en tiles del objeto. */
    int get_width() const;

    /* Devuelve la altura en tiles del objeto. */
    int get_height() const;

    /* Devuelve el offset total de renderizacion en centesimas de tile. */
    virtual int get_x_offset() const;
    virtual int get_y_offset() const;

    RenderizableObject(const RenderizableObject& other);
    RenderizableObject& operator=(const RenderizableObject& other);
    /* Debe ser llamado luego de renderizar para actualizar el estado de las
    constantes visuales.*/
    virtual void update();
};

#endif
