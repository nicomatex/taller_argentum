#include "game_view.h"

#include "../../client_config.h"
#include "../../engine/ECS/entity.h"
#include "../../engine/ECS/entity_manager.h"
#include "../../engine/UI/stat_bar.h"
#include "../../engine/entity_factory.h"
#include "../../engine/resource_manager.h"
#include "../responsive_scaler.h"

GameView::GameView(ResponsiveScaler &scaler, int follow_entity_id,
                   SocketManager &socket_manager, SDLWindow &window,
                   ChatBuffer &chat_buffer, InventoryBuffer &inventory_buffer,
                   GameStateMonitor &game_state_monitor,
                   nlohmann::json map_info)
    : scaler(scaler),
      window(window),
      chat_buffer(chat_buffer),
      game_state_monitor(game_state_monitor),
      hud(scaler, window, chat_buffer, inventory_buffer,
          EntityManager::get_instance().get_from_id(follow_entity_id),
          socket_manager),
      camera(EntityManager::get_instance()
                 .get_from_id(follow_entity_id)
                 .get_component<PositionComponent>(),
             scaler.scale(VIEWPORT_MAIN_RENDER), map_info["width"],
             scaler.simple_scale(TILE_SIZE), VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
             CAMERA_SPEED),
      ui_event_handler(socket_manager, game_state_monitor, hud, camera,
                       scaler.scale(VIEWPORT_MAIN_RENDER)),
      map(map_info) {}

GameView::~GameView() {}

void GameView::run() {
    SDL_Rect main_render_viewport = scaler.scale(VIEWPORT_MAIN_RENDER);
    ResourceManager::get_instance().get_music(2).play();
    game_state_monitor.set_game_state(RUNNING);
    while (game_state_monitor.get_game_state() == RUNNING) {
        window.fill(0, 0, 0, 255);

        ui_event_handler.handle();

        EntityManager::get_instance().update();
        hud.update();
        camera.update();

        window.set_viewport(main_render_viewport);
        camera.render_map_layers(map.get_background_layers());
        camera.draw_all();
        camera.render_map_layers(map.get_foreground_layers());
        hud.render();
        window.render();
    }
    EntityManager::get_instance().empty();
}