#ifndef __HUD_H
#define __HUD_H
#include "../../chat_buffer.h"
#include "../../engine/ECS/entity.h"
#include "../../engine/SDL/sdl_text.h"
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/icon_grid.h"
#include "../../engine/UI/stat_bar.h"
#include "../../inventory_buffer.h"
#include "../responsive_scaler.h"
#include "SDL2/SDL.h"
#include "cast_button.h"
#include "chat.h"
#include "inventory.h"

class StatsComponent;

class Hud {
   private:
    ResponsiveScaler& scaler;
    SDLWindow& window;
    Entity& player;
    ChatBuffer& chat_buffer;
    InventoryBuffer& inventory_buffer;
    Chat chat;
    StatBar mana_bar;
    StatBar health_bar;
    StatBar experience_bar;
    IconGrid equipped_items;
    Inventory inventory;
    bool attempting_cast;
    CastButton cast_button;
    SDLTexture& side_panel_background;
    SDLText gold_text;
    SDLText level_text;

    friend class UiEventHandler;

    void _render_gold_amount();
    void _render_level();

    void _update_stats();
    void _update_inventory();
    void _update_equipped_items();

   public:
    Hud(ResponsiveScaler& scaler, SDLWindow& window, ChatBuffer& chat_buffers,
        InventoryBuffer& inventory_buffer, Entity& player,
        SocketManager& socket_manager);
    ~Hud();

    void handle_event(SDL_Event& e);

    void update();
    void render();
};

#endif