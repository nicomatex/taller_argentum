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
#include "views/character_creation_view/character_creation_view.h"
#include "views/game_view/game_view.h"
#include "views/login_view/login_view.h"
#include "views/responsive_scaler.h"
#include "engine/asset_loading_error.h"

using json = nlohmann::json;

GameClient::GameClient(json config)
    : window(config["window_width"], config["window_height"], WINDOW_TITLE,
             config["fullscreen"]),
      socket_manager(
          Socket(std::string(config["server"]), std::string(config["port"])),
          receive_handler),
      config(config),
      receive_handler(map_change_buffer, chat_buffer, inventory_buffer, loot_buffer,
                      game_state_monitor) {
    SDLTextureLoader texture_loader(window.init_renderer());
    try{
        ResourceManager::get_instance().init(texture_loader);
    }catch(AssetLoadingError &e){
        std::cerr << e.what() << std::endl;
        std::cerr << "Is the game installed correctly? run 'make install' " << std::endl;
        throw;
    }
    receive_handler.start();
    socket_manager.start();
    game_state_monitor.set_connected_status(true);
}

void GameClient::run() {
    ResponsiveScaler scaler(window, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_Volume(-1, MIX_MAX_VOLUME / 3);
    game_state_monitor.set_game_state(LOGGING);
    while (game_state_monitor.is_connected()) {
        switch (game_state_monitor.get_game_state()) {
            case LOGGING:
                LoginView(window, scaler, game_state_monitor, socket_manager)
                    .run();
                break;
            case READY_TO_RUN:
                GameView(scaler, map_change_buffer.get_follow_entity_id(),
                         socket_manager, window, chat_buffer, inventory_buffer,
                         loot_buffer,
                         game_state_monitor, map_change_buffer.get_map_info())
                    .run();
                break;
            case SWITCHING_MAPS:
                game_state_monitor.set_game_state(WAITING_FOR_INITIALIZATION);
                break;
            case CREATING_CHARACTER:
                CharacterCreationView(window, scaler, game_state_monitor,
                                      socket_manager)
                    .run();
                break;
            default:
                game_state_monitor.wait_for_next_game_state();
                break;
        }
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