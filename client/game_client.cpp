#include "game_client.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "client_config.h"
#include "engine/ECS/entity.h"
#include "engine/SDL/sdl_animated_sprite.h"
#include "engine/SDL/sdl_error.h"
#include "engine/SDL/sdl_window.h"
#include "engine/actor.h"
#include "engine/animation_pack.h"
#include "engine/camera.h"
#include "engine/components/position_component.h"
#include "engine/components/visual_character_component.h"
#include "engine/entity_factory.h"
#include "engine/json.hpp"
#include "engine/map.h"
#include "engine/renderizable_object.h"
#include "engine/resource_manager.h"
#include <thread>

using json = nlohmann::json;

GameClient::GameClient(const std::string &texture_index_file,
                       const std::string &sprite_index_file)
    : main_window(960, 640, "Argentum Online"),
      entitiy_factory(entity_manager), socket_manager(0,Socket("localhost","8080")) {
    try {
        SDLTextureLoader texture_loader(main_window.init_renderer());
        ResourceManager::get_instance().init(texture_loader);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    socket_manager.start();
}

void GameClient::_update_game(SDL_Event &e) {}

void GameClient::_update_components(SDL_Event &e, Entity &player) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        PositionComponent &playerpos =
            player.get_component<PositionComponent>();
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                playerpos.set_position(playerpos.get_x() + 1,
                                       playerpos.get_y());
                break;
            case SDLK_LEFT:
                playerpos.set_position(playerpos.get_x() - 1,
                                       playerpos.get_y());
                break;
            case SDLK_UP:
                playerpos.set_position(playerpos.get_x(),
                                       playerpos.get_y() - 1);
                break;
            case SDLK_DOWN:
                playerpos.set_position(playerpos.get_x(),
                                       playerpos.get_y() + 1);
                break;
        }
    }
}

void GameClient::_poll_events() {
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                //socket_manager.stop(true);
            }
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        json command;
                        command["event_id"] = 0;
                        command["type"] = "start";
                        command["orientation"] = "right";
                        socket_manager.send(Event(command));
                        break;
                }
            }
        }
    }
}

void GameClient::run() {
    running = true;
    Entity &player = entitiy_factory.create_player(0,1, 1, 0, 0);
    Entity &another_player = entitiy_factory.create_player(1,1,2,0,0);
    Actor &body =
        player.get_component<VisualCharacterComponent>().get_part("body");
    Camera camera(body, 50, 64);
    player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
    another_player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
    another_player.get_component<PositionComponent>().set_position(5,5);
    Map map("assets/maps/forest1.json",
            ResourceManager::get_instance().get_texture("tilesets", 1));
    std::thread event_thread(&GameClient::_poll_events,this);

    SDLTimer head_timer;
    head_timer.start();

    while (running) {
        main_window.fill(0, 0, 0, 255);
        entity_manager.update();
        camera.update_position();
        camera.render_map_layer(map.get_layer(0));
        camera.render_map_layer(map.get_layer(1));
        entity_manager.draw();
        main_window.render();
        if(head_timer.get_ticks() >= 5000){
            player.get_component<VisualCharacterComponent>().set_head(2);
            player.get_component<VisualCharacterComponent>().set_body(2);
            head_timer.stop();
            Entity &yet_another_player = entitiy_factory.create_player(2,3,3,0,0);
            yet_another_player.get_component<VisualCharacterComponent>().bind_to_camera(camera);
            yet_another_player.get_component<PositionComponent>().set_position(6,9);
            another_player.kill();
            entity_manager.clean();
        }
    }
    std::cout << "llegue a salir del bucle" << std::endl;
    //socket_manager.join();
    event_thread.join();
    socket_manager.stop(true);
    socket_manager.join();
    std::cout << "Llegue a joinear el event thread" << std::endl;
}

GameClient::~GameClient() {}