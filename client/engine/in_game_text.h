#ifndef __IN_GAME_TEXT_H
#define __IN_GAME_TEXT_H
#include "SDL/sdl_bitmap_text.h"
#include "renderizable_object.h"

/**
 * @brief Clase usada para mostrar texto del render, mediante texto bitmap.
 *
 */
class InGameText : public RenderizableObject {
   private:
    SDLBitmapText render_text;

   public:
    /**
     * @brief Crea un objeto In Game Text
     *
     * @param text Texto a mostrar.
     * @param color Color del texto.
     * @param font_id id de la fuente bitmap a usar.
     * @param visual_info Informacion visual para renderizar el texto.
     */
    InGameText(const std::string& text, SDL_Color color, int font_id,
               visual_info_t visual_info);

    /**
     * @brief Renderiza el texto en pantalla.
     *
     * @param dest Rectangulo de pantalla donde se debe renderizar el texto.
     */
    void render(SDL_Rect dest) override;

    /**
     * @brief Actualiza el texto.
     * 
     * @param new_text Nuevo texto a mostrar.
     */
    void update_text(const std::string& new_text);
};

#endif