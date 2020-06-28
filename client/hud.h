#ifndef __HUD_H
#define __HUD_H
#include "SDL2/SDL.h"
#include "chat.h"
#include "chat_buffer.h"
#include "engine/SDL/sdl_texture.h"
#include "engine/SDL/sdl_window.h"
#include "engine/UI/stat_bar.h"

class StatsComponent;

class Hud {
   private:
    SDLWindow& window;
    StatsComponent& player_stats;
    ChatBuffer& chat_buffer;
    Chat chat;
    StatBar mana_bar;
    StatBar health_bar;
    // StatBar experience_bar;
    SDLTexture& side_panel_background;
    friend class UiEventHandler;

   public:
    Hud(SDLWindow& window, ChatBuffer& chat_buffers,
        StatsComponent& player_stats);
    ~Hud();

    void update();
    void render();
};

#endif