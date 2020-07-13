#ifndef __MAIN_GAME_WINDOW_H
#define __MAIN_GAME_WINDOW_H
#include <atomic>

#include "../../../include/network/socket_manager.h"
#include "../../../include/nlohmann/json.hpp"
#include "../../chat_buffer.h"
#include "../../engine/SDL/sdl_window.h"
#include "../../engine/camera.h"
#include "../../engine/map.h"
#include "../../game_state_monitor.h"
#include "../../inventory_buffer.h"
#include "../../loot_buffer.h"
#include "../../player_info_monitor.h"
#include "../responsive_scaler.h"
#include "hud.h"
#include "ui_event_handler.h"

/**
 * @brief Vista principal del juego.
 *
 */
class GameView {
   private:
    ResponsiveScaler &scaler;
    SDLWindow &window;
    LootBuffer &loot_buffer;
    ChatBuffer &chat_buffer;
    GameStateMonitor &game_state_monitor;
    Hud hud;
    Camera camera;
    UiEventHandler ui_event_handler;
    Map map;

   public:
    /**
     * @brief Constructor de la vista principal.
     *
     * @param scaler Escalador para responsiveness.
     * @param follow_entity_id Id de la entidad que la camara debe seguir.
     * @param socket_manager Socket manager del juego.
     * @param window Ventana donde se va a renderizar el juego.
     * @param chat_buffer Buffer de chat.
     * @param inventory_buffer Buffer de inventario.
     * @param loot_buffer Buffer de loot.
     * @param game_state_monitor Monitor de estado del juego.
     * @param map_info json que contiene la informacion visual para construir el
     * mapa.
     */
    GameView(ResponsiveScaler &scaler, int follow_entity_id,
             SocketManager &socket_manager, SDLWindow &window,
             ChatBuffer &chat_buffer, InventoryBuffer &inventory_buffer,
             LootBuffer &loot_buffer, PlayerInfoMonitor &player_info_monitor,
             GameStateMonitor &game_state_monitor, nlohmann::json map_info);

    /**
     * @brief Inicia la vista.
     *
     */
    void run();

    ~GameView();
};

#endif