#include "game_view.h"

#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/ECS/entity_manager.h"
#include "engine/UI/stat_bar.h"
#include "engine/resource_manager.h"
#include "responsive_scaler.h"
GameView::GameView(ResponsiveScaler &scaler, int follow_entity_id,
                   SocketManager &socket_manager, SDLWindow &window,
                   ChatBuffer &chat_buffer,
                   GameStateMonitor &game_state_monitor,
                   nlohmann::json map_info)
    : scaler(scaler),
      window(window),
      chat_buffer(chat_buffer),
      game_state_monitor(game_state_monitor),
      hud(scaler, window, chat_buffer,
          EntityManager::get_instance()
              .get_from_id(follow_entity_id)
              .get_component<StatsComponent>()),
      ui_event_handler(socket_manager, game_state_monitor, hud),
      camera(EntityManager::get_instance()
                 .get_from_id(follow_entity_id)
                 .get_component<PositionComponent>(),
             map_info["width"], scaler.simple_scale(TILE_SIZE), VIEWPORT_WIDTH,
             VIEWPORT_HEIGHT, CAMERA_SPEED),
      map(map_info) {}

GameView::~GameView() {}

void GameView::run() {
    SDL_Rect main_render_viewport = scaler.scale(VIEWPORT_MAIN_RENDER);

    while (game_state_monitor.get_game_state() == RUNNING) {
        window.fill(0, 0, 0, 255);

        ui_event_handler.handle();

        EntityManager::get_instance().update();
        hud.update();
        camera.update();

        window.set_viewport(main_render_viewport);
        camera.render_map_layer(map.get_layer(0));
        camera.render_map_layer(map.get_layer(1));
        camera.draw_all();
        camera.render_map_layer(map.get_layer(2));
        hud.render();
        window.render();
    }
    EntityManager::get_instance().empty();
}