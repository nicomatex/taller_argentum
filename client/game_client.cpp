#include "game_client.h"

#include <fstream>
#include <iomanip>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "SDL2/SDL.h"
#include "client_config.h"
#include "engine/SDL/sdl_music.h"
#include "engine/SDL/sdl_window.h"
#include "engine/entity_factory.h"
#include "engine/map.h"
#include "engine/resource_manager.h"
#include "views/game_view.h"
#include "views/responsive_scaler.h"
#include "views/login_view.h"

using json = nlohmann::json;

GameClient::GameClient(json config)
    : window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, WINDOW_TITLE,
             config["fullscreen"]),
      socket_manager(
          Socket(std::string(config["server"]), std::string(config["port"])),
          receive_handler),
      config(config),
      receive_handler(map_change_buffer, chat_buffer, game_state_monitor) {
    // window.hide();
    SDLTextureLoader texture_loader(window.init_renderer());
    ResourceManager::get_instance().init(texture_loader);
    receive_handler.start();
    socket_manager.start();
    game_state_monitor.set_connected_status(true);
}

void GameClient::run() {
    ResponsiveScaler scaler(window, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_Volume(-1, MIX_MAX_VOLUME / 3);
    game_state_monitor.set_game_state(LOGGING);
    {
        LoginView login_view(window, scaler, game_state_monitor, socket_manager);
        login_view.run();
    }
    ResourceManager::get_instance().get_music(2).play();

    while (game_state_monitor.is_connected()) {
        game_state_monitor.set_game_state(WAITING_FOR_INITIALIZATION);
        map_change_buffer.wait_for_map();
        game_state_monitor.set_game_state(RUNNING);

        GameView game(scaler, map_change_buffer.get_follow_entity_id(),
                      socket_manager, window, chat_buffer, game_state_monitor,
                      map_change_buffer.get_map_info());
        game.run();

        if (!socket_manager.is_connected()) {
            std::cout << MSG_ERR_CONECT_DROPPED << std::endl;
            game_state_monitor.set_connected_status(false);
        }
    }
    receive_handler.stop();
    receive_handler.join();
    socket_manager.stop(true);
    socket_manager.join();
}

GameClient::~GameClient() { ResourceManager::get_instance().free_resources(); }