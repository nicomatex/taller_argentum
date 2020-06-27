#ifndef __HUD_H
#define __HUD_H
#include "SDL2/SDL.h"
#include "chat.h"
#include "chat_buffer.h"
#include "engine/SDL/sdl_texture.h"
#include "engine/SDL/sdl_window.h"
#include "engine/UI/stat_bar.h"

class Hud {
   private:
    Chat chat;
    StatBar mana_bar;
    StatBar health_bar;
    // StatBar experience_bar;
    ChatBuffer& chat_buffer;
    SDLWindow& window;
    SDLTexture& side_panel_background;
    friend class UiEventHandler;

   public:
    Hud(SDLWindow& window, ChatBuffer& chat_buffer, unsigned int max_hp,
        unsigned int max_mp);
    ~Hud();

    void update();
    void render();
};

#endif