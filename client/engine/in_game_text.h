#ifndef __IN_GAME_TEXT_H
#define __IN_GAME_TEXT_H
#include "renderizable_object.h"
#include "SDL/sdl_text.h"

class InGameText : public RenderizableObject {
   private:
    SDLText render_text;
    std::string get_offseted_text(const std::string& text, int padded_size);

   public:
    InGameText(visual_info_t visual_info, std::string text, int max_size);

    void update_text(const std::string& text);
    
    void render(SDL_Rect dest) override;
};

#endif