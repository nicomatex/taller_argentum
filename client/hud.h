#ifndef __HUD_H
#define __HUD_H
#include "SDL2/SDL.h"
#include "chat.h"
#include "chat_buffer.h"
#include "engine/SDL/sdl_texture.h"
#include "engine/SDL/sdl_window.h"
#include "engine/UI/stat_bar.h"
#include "engine/UI/icon_grid.h"
#include "cast_button.h"
#include "responsive_scaler.h"
#include "engine/ECS/entity.h"
class StatsComponent;

class Hud {
   private:
    ResponsiveScaler &scaler;
    SDLWindow& window;
    Entity& player;
    ChatBuffer& chat_buffer;
    Chat chat;
    StatBar mana_bar;
    StatBar health_bar;
    // StatBar experience_bar;
    IconGrid equipped_items;
    CastButton cast_button;
    SDLTexture& side_panel_background;
    friend class UiEventHandler;

    void _update_stat_bars();
    void _update_equipped_items();
    
   public:
    Hud(ResponsiveScaler &scaler,SDLWindow& window, ChatBuffer& chat_buffers,
        Entity& player);
    ~Hud();

    void handle_event(SDL_Event &e);

    void update();
    void render();
};

#endif