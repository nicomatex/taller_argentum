#include <fstream>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "client_config.h"
#include "game_client.h"

bool debug = true;

using json = nlohmann::json;

int main(void) {
    json config;
    try {
        std::ifstream config_file(CLIENT_CONFIG_FILE);
        config = json::parse(config_file);
    } catch (std::exception &e) {
        std::cerr << MSG_ERR_CONFIG_FILE << std::endl;
        return 1;
    }

    try {
        GameClient game(config);
        game.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}