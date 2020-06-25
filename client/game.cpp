#include "game.h"

#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/ECS/entity_manager.h"
#include "engine/resource_manager.h"

Game::Game(int follow_entity_id, SocketManager &socket_manager,
           SDLWindow &window, ChatBuffer &chat_buffer,
           GameStateMonitor &game_state_monitor, nlohmann::json map_info)
    : ui_event_handler(socket_manager, game_state_monitor),
      camera(EntityManager::get_instance()
                 .get_from_id(follow_entity_id)
                 .get_component<PositionComponent>(),
             map_info["width"], TILE_SIZE, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, CAMERA_SPEED),
      window(window),
      chat_buffer(chat_buffer),
      game_state_monitor(game_state_monitor) {
          map.generate(map_info);
      }

Game::~Game() {}

void Game::run() {
    Chat chat(AREA_CHAT, CHAT_LINES, window.get_renderer(),
              ResourceManager::get_instance().get_font(1));
    ui_event_handler.attach_chat(&chat);
    while (game_state_monitor.is_running()) {
        window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        EntityManager::get_instance().update();
        window.set_viewport(AREA_MAIN_RENDER);
        camera.update();
        camera.render_map_layer(map.get_layer(0));
        camera.render_map_layer(map.get_layer(1));
        camera.draw_all();
        camera.render_map_layer(map.get_layer(2));
        window.set_viewport(AREA_CHAT);
        chat_buffer.flush(chat);
        chat.render();
        window.set_viewport(AREA_SIDE_PANEL);
        SDL_SetRenderDrawColor(window.get_renderer(), 100, 100, 100,
                               255);             // Temporal
        SDL_Rect side_panel = {0, 0, 260, 960};  // Temporal
        SDL_RenderFillRect(window.get_renderer(),
                           &side_panel);  // Temporal
        window.render();
    }
    EntityManager::get_instance().empty();
}