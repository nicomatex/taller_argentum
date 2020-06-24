#include "game.h"

#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/ECS/entity_manager.h"
#include "engine/resource_manager.h"

Game::Game(int follow_entity_id, SocketManager &socket_manager,
           SDLWindow &window, ChatBuffer &chat_buffer)
    : running(true),
      ui_event_handler(socket_manager, running),
      camera(EntityManager::get_instance()
                 .get_from_id(follow_entity_id)
                 .get_component<PositionComponent>(),
             50, TILE_SIZE, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, CAMERA_SPEED),
      window(window),
      chat_buffer(chat_buffer) {}

Game::~Game() {}

void Game::setup_map(nlohmann::json map_info) { map.generate(map_info); }

void Game::run() {
    Chat chat(AREA_CHAT, CHAT_LINES, window.get_renderer(),
              ResourceManager::get_instance().get_font(1));
    ui_event_handler.attach_chat(&chat);
    while (running) {
        window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        EntityManager::get_instance().update();
        window.set_viewport(AREA_MAIN_RENDER);
        camera.update();
        camera.render_map_layer(map.get_layer(0));
        camera.draw_all();
        camera.render_map_layer(map.get_layer(1));
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
}