#include "game.h"

#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/ECS/entity_manager.h"
#include "engine/UI/stat_bar.h"
#include "engine/resource_manager.h"

Game::Game(int follow_entity_id, SocketManager &socket_manager,
           SDLWindow &window, ChatBuffer &chat_buffer,
           GameStateMonitor &game_state_monitor, nlohmann::json map_info)
    : window(window),
      chat_buffer(chat_buffer),
      game_state_monitor(game_state_monitor),
      hud(window, chat_buffer,
          EntityManager::get_instance()
              .get_from_id(follow_entity_id)
              .get_component<StatsComponent>()),
      ui_event_handler(socket_manager, game_state_monitor, hud),
      camera(EntityManager::get_instance()
                 .get_from_id(follow_entity_id)
                 .get_component<PositionComponent>(),
             map_info["width"], TILE_SIZE, VIEWPORT_WIDTH, VIEWPORT_HEIGHT,
             CAMERA_SPEED),
      map(map_info) {}

Game::~Game() {}

void Game::run() {
    while (game_state_monitor.is_running()) {
        window.fill(0, 0, 0, 255);

        ui_event_handler.handle();

        EntityManager::get_instance().update();
        hud.update();
        camera.update();

        window.set_viewport(VIEWPORT_MAIN_RENDER);
        camera.render_map_layer(map.get_layer(0));
        camera.render_map_layer(map.get_layer(1));
        camera.draw_all();
        camera.render_map_layer(map.get_layer(2));
        hud.render();
        window.render();
    }
    EntityManager::get_instance().empty();
}