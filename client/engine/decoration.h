#ifndef __DECORATION_H
#define __DECORATION_H

#include "SDL/sdl_animated_sprite.h"
#include "renderizable_object.h"

/**
 * @brief Objeto renderizable estatico.
 * 
 */
class Decoration : public RenderizableObject {
   private:
    SDLSprite sprite;
    int x, y;

   public:
    /**
     * @brief Crea un objeto Decoration
     *
     * @param sprite Sprite asociado a la decoracion.
     * @param x Tile X donde se va a renderizar la decoracion.
     * @param y Tile Y donde se va a renderizar la decoracion.
     * @param visual_info Struct de informacion visual.
     */
    Decoration(SDLSprite sprite, int x, int y, visual_info_t visual_info);

    /**
     * @brief Devuelve la coordenda X.
     *
     * @return int
     */
    int get_x() const;

    /**
     * @brief Devuelve la coordenada Y.
     *
     * @return int
     */
    int get_y() const;

    /**
     * @brief Renderiza el objeto en pantalla.
     *
     * @param dest Cuadro en pantalla donde se va a renderizar.
     */
    void render(SDL_Rect dest) override;
};

#endif
