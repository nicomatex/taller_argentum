#ifndef __HUD_H
#define __HUD_H
#include "../../chat_buffer.h"
#include "../../engine/ECS/entity.h"
#include "../../engine/SDL/sdl_bitmap_text.h"
#include "../../engine/SDL/sdl_text.h"
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/UI/stat_bar.h"
#include "../../inventory_buffer.h"
#include "../../player_info_monitor.h"
#include "../responsive_scaler.h"
#include "SDL2/SDL.h"
#include "cast_button.h"
#include "chat.h"
#include "equipment.h"
#include "inventory.h"

class StatsComponent;
/**
 * @brief HUD del juego (informacion del jugador).
 *
 */
class Hud {
   private:
    ResponsiveScaler& scaler;
    SDLWindow& window;
    Entity& player;
    ChatBuffer& chat_buffer;
    InventoryBuffer& inventory_buffer;
    PlayerInfoMonitor& player_info_monitor;
    Chat chat;
    StatBar mana_bar;
    StatBar health_bar;
    StatBar experience_bar;
    // IconGrid equipped_items;
    Equipment equipment;
    Inventory inventory;
    bool attempting_cast;
    bool render_help;
    CastButton cast_button;
    SDLTexture& side_panel_background;
    SDLTexture& help_panel;
    SDLText gold_text;
    SDLText level_text;
    SDLText spell_name_text;
    SDLText attack_points_text;
    SDLText defense_points_text;
    friend class UiEventHandler;

    SDL_Rect _get_scaled_dest(SDLText &text,SDL_Rect dest);

    void _render_gold_amount();
    void _render_level();
    void _render_player_info();
    void _render_help_panel();

    void _update_stats();
    void _update_inventory();
    void _update_equipment();
    void _update_player_info();
    
   public:
    /**
     * @brief Constructor de hud.
     *
     * @param scaler Escaler para responsiveness.
     * @param window Ventana del juego.
     * @param chat_buffers Buffer de chat.
     * @param inventory_buffer Buffer de inventario.
     * @param player Entidad del jugador.
     * @param socket_manager Socket manager del juego.
     */
    Hud(ResponsiveScaler& scaler, SDLWindow& window, ChatBuffer& chat_buffers,
        InventoryBuffer& inventory_buffer,
        PlayerInfoMonitor& player_info_monitor, Entity& player,
        SocketManager& socket_manager);
    ~Hud();

    /**
     * @brief Realiza las modificaciones / acciones necesarias segun el evento.
     *
     * @param e
     */
    void handle_event(SDL_Event& e);

    /**
     * @brief Actualiza el HUD
     *
     */
    void update();

    /**
     * @brief Renderiza el HUD
     *
     */
    void render();
};

#endif