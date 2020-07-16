#ifndef __IN_GAME_BAR_H
#define __IN_GAME_BAR_H

#include "renderizable_object.h"

/**
 * @brief Clase usada para mostrar una barra del render.
 *
 */
class InGameBar : public RenderizableObject {
   private:
    float fill_proportion;
    SDL_Color color;
    SDLTexture& bar_texture;

   public:
    InGameBar(visual_info_t visual_info, SDL_Color color);
    ~InGameBar();

    void render(SDL_Rect dest) override;
};

#endif
