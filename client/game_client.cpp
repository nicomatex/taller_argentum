#include "game_client.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include "SDL2/SDL.h"
#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/SDL/sdl_area.h"
#include "engine/SDL/sdl_text.h"
#include "engine/SDL/sdl_window.h"
#include "engine/actor.h"
#include "engine/camera.h"
#include "engine/components/position_component.h"
#include "engine/components/visual_character_component.h"
#include "engine/entity_factory.h"
#include "engine/json.hpp"
#include "engine/map.h"
#include "engine/resource_manager.h"
#include "chat.h"

using json = nlohmann::json;

GameClient::GameClient(json config)
    : main_window(int(config["window width"]), int(config["window height"]),
                  WINDOW_TITLE),
      entity_factory(entity_manager),
      ready(false),
      receive_handler(entity_manager, current_map, ready, running),
      socket(std::string(config["server"]), std::string(config["port"])),
      socket_manager(socket, receive_handler),
      ui_event_handler(running, socket_manager),
      config(config) {
    try {
        SDLTextureLoader texture_loader(main_window.init_renderer());
        ResourceManager::get_instance().init(texture_loader);
        socket_manager.send(event_factory.connect_event("nicolito", "1234"));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    receive_handler.start();
    socket_manager.start();
}

void GameClient::run() {
    while (!ready) {}  // Esperamos que se complete la carga
    
    running = true;
    Entity &player = entity_factory.create_player(0, 1, 1, 0, 0);
    Camera camera(player.get_component<PositionComponent>(), 50, TILE_SIZE, 11, 8,3);
    player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
    SDLArea render_area(0, 128, 700, 512);

    SDLArea side_panel_area(700,0,260,960); //Temporal

    /* Generacion de la UI */
    SDLArea chat_area(0,0,700,128);
    Chat chat(chat_area,8,main_window.get_renderer());
    ui_event_handler.attach_chat(&chat);
    while (running && socket_manager.is_connected()) {
        main_window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        entity_manager.update();
        main_window.set_viewport(render_area);
        camera.update();
        camera.render_map_layer(current_map.get_layer(0));
        camera.render_map_layer(current_map.get_layer(1));
        entity_manager.draw();
        main_window.set_viewport(chat_area);
        chat.render();
        main_window.set_viewport(side_panel_area);
        SDL_SetRenderDrawColor(main_window.get_renderer(),100,100,100,255);
        SDL_Rect side_panel = {0,0,260,960};
        SDL_RenderFillRect(main_window.get_renderer(),&side_panel);
        main_window.render();
    }
    if (!socket_manager.is_connected()) {
        std::cout << MSG_ERR_CONECT_DROPPED << std::endl;
    }
    receive_handler.stop();
    receive_handler.join();
    socket_manager.stop(true);
    socket_manager.join();
}

GameClient::~GameClient() {}