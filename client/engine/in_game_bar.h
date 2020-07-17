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
    SDLTexture& bar_texture;

   public:
    InGameBar(visual_info_t visual_info);

    void set_fill_proportion(float fill_proportion);

    void render(SDL_Rect dest) override;
};

#endif
