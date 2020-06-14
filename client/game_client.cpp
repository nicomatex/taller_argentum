#include "game_client.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

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
      entitiy_factory(entity_manager),
      receive_handler(entity_manager),
      socket(std::string(config["server"]), std::string(config["port"])),
      socket_manager(socket, (BlockingThEventHandler *)&receive_handler) {
    try {
        SDLTextureLoader texture_loader(main_window.init_renderer());
        ResourceManager::get_instance().init(texture_loader);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    socket_manager.start();
}

void GameClient::_poll_events() {
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        socket_manager.send(
                            event_factory.movement_event(START, UP));
                        break;
                    case SDLK_DOWN:
                        socket_manager.send(
                            event_factory.movement_event(START, DOWN));
                        break;
                    case SDLK_RIGHT:
                        socket_manager.send(
                            event_factory.movement_event(START, RIGHT));
                        break;
                    case SDLK_LEFT:
                        socket_manager.send(
                            event_factory.movement_event(START, LEFT));
                        break;
                }
            } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        socket_manager.send(
                            event_factory.movement_event(STOP, UP));
                        break;
                    case SDLK_DOWN:
                        socket_manager.send(
                            event_factory.movement_event(STOP, DOWN));
                        break;
                    case SDLK_RIGHT:
                        socket_manager.send(
                            event_factory.movement_event(STOP, RIGHT));
                        break;
                    case SDLK_LEFT:
                        socket_manager.send(
                            event_factory.movement_event(STOP, LEFT));
                        break;
                }
            }
        }
    }
}

void GameClient::run() {
    running = true;
    Entity &player = entitiy_factory.create_player(0, 1, 1, 0, 0);
    Entity &another_player = entitiy_factory.create_player(1, 1, 2, 0, 0);
    Actor &body =
        player.get_component<VisualCharacterComponent>().get_part("body");
    Camera camera(body, 50, 64, 15, 8);
    player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
    another_player.get_component<VisualCharacterComponent>().bind_to_camera(
        camera);
    another_player.get_component<PositionComponent>().set_position(5, 5);
    std::ifstream map_file("assets/maps/forest1.json");
    json map_info = json::parse(map_file);
    current_map.generate(map_info);
    std::thread event_thread(&GameClient::_poll_events, this);

    SDLTimer head_timer;
    head_timer.start();
    SDLArea render_area(0, 128, 960, 512);

    main_window.set_viewport(render_area);
    while (running) {
        main_window.fill(0, 0, 0, 255);
        entity_manager.update();
        camera.update_position();
        camera.render_map_layer(current_map.get_layer(0));
        camera.render_map_layer(current_map.get_layer(1));
        entity_manager.draw();
        main_window.render();
        if (head_timer.get_ticks() >= 5000) {
            player.get_component<VisualCharacterComponent>().set_head(2);
            player.get_component<VisualCharacterComponent>().set_body(2);
            head_timer.stop();
            Entity &yet_another_player =
                entitiy_factory.create_player(2, 3, 3, 0, 0);
            yet_another_player.get_component<VisualCharacterComponent>()
                .bind_to_camera(camera);
            yet_another_player.get_component<PositionComponent>().set_position(
                6, 9);
            another_player.kill();
            entity_manager.clean();
        }
    }
    socket_manager.stop(true);
    event_thread.join();
    socket_manager.join();
}

GameClient::~GameClient() {}