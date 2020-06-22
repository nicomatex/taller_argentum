#include "game_client.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>

#include "SDL2/SDL.h"
#include "chat.h"
#include "client_config.h"
#include "engine/ECS/entity.h"
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
#include "game.h"

using json = nlohmann::json;

GameClient::GameClient(json config)
    : window(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT,
             WINDOW_TITLE),
      socket_manager(Socket(std::string(config["server"]),
                     std::string(config["port"])), receive_handler),
      config(config),
      receive_handler(map_change_buffer, chat_buffer) {
    try {
        std::cout << R"(
   _____                                      __                       ________           .__   .__                 
  /  _  \  _______    ____    ____    ____  _/  |_  __ __   _____      \_____  \    ____  |  |  |__|  ____    ____
 /  /_\  \ \_  __ \  / ___\ _/ __ \  /    \ \   __\|  |  \ /     \      /   |   \  /    \ |  |  |  | /    \ _/ __ \
/    |    \ |  | \/ / /_/  >\  ___/ |   |  \ |  |  |  |  /|  Y Y  \    /    |    \|   |  \|  |__|  ||   |  \\  ___/
\____|__  / |__|    \___  /  \___  >|___|  / |__|  |____/ |__|_|  /    \_______  /|___|  /|____/|__||___|  / \___  >
        \/         /_____/       \/      \/                     \/             \/      \/                \/      \/
)"      << std::endl;
        std::string char_name;
        std::string password;
        std::cout << "Usuario: "; 
        std::cin >> char_name;
        std::cout << "Contraseña: ";
        std::cin >> password;
        SDLTextureLoader texture_loader(window.init_renderer());
        ResourceManager::get_instance().init(texture_loader);
        socket_manager.send(EventFactory::connect_event(char_name, password));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    receive_handler.start();
    socket_manager.start();
}

void GameClient::run() {
    map_change_buffer.wait_for_map();
    Game game(map_change_buffer.get_follow_entity_id(), socket_manager, window,
              chat_buffer);
    game.setup_map(map_change_buffer.get_map_info());

    game.run();
    if (!socket_manager.is_connected()) {
        std::cout << MSG_ERR_CONECT_DROPPED << std::endl;
    }
    receive_handler.stop();
    receive_handler.join();
    socket_manager.stop(true);
    socket_manager.join();
}

GameClient::~GameClient() { ResourceManager::get_instance().free_resources(); }