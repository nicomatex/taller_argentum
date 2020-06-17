#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include "game_client.h"
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

using json = nlohmann::json;

GameClient::GameClient(json config)
    : main_window(int(config["window width"]), int(config["window height"]),
                  WINDOW_TITLE),
      entity_factory(entity_manager),
      receive_handler(entity_manager, current_map),
      socket(std::string(config["server"]), std::string(config["port"])),
      socket_manager(socket, receive_handler),
      ui_event_handler(running, socket_manager) {
    try {
        SDLTextureLoader texture_loader(main_window.init_renderer());
        ResourceManager::get_instance().init(texture_loader);
        socket_manager.send(event_factory.connect_event("nicolito","1234"));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    socket_manager.start();
}

void GameClient::run() {
    // while(!ready){} //Esperamos que se complete la carga

    running = true;
    Entity &player = entity_factory.create_player(0, 1, 1, 0, 0);
    Actor &body = player.get_component<VisualCharacterComponent>().get_part("body");
    Camera camera(body, 50, TILE_SIZE, 15, 8);
    player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
    std::ifstream map_file("assets/maps/forest1.json");
    json map_info = json::parse(map_file);
    current_map.generate(map_info);
    SDLArea render_area(0, 128, 960, 512);
    main_window.set_viewport(render_area);

    while (running && socket_manager.is_connected()) {
        main_window.fill(0, 0, 0, 255);
        ui_event_handler.handle();
        entity_manager.update();
        camera.update_position();
        camera.render_map_layer(current_map.get_layer(0));
        camera.render_map_layer(current_map.get_layer(1));
        entity_manager.draw();
        main_window.render();
    }
    if(!socket_manager.is_connected()){
        std::cout << MSG_ERR_CONECT_DROPPED << std::endl;
    }

    socket_manager.stop(true);
    socket_manager.join();
}

GameClient::~GameClient() {}