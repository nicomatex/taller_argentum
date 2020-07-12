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
        if (!config_file.is_open()) {
            if (chdir("/usr/local/share/argentum") < 0) {
                std::cerr
                    << "Config file not found. Is the game installed correctly?"
                    << std::endl;
                return -1;
            }
            config_file.open(CLIENT_CONFIG_FILE);
        }
        config = json::parse(config_file);
    } catch (std::exception &e) {
        std::cerr << MSG_ERR_CONFIG_FILE << std::endl;
        return 1;
    }

    try {
        GameClient game(config);
        game.run();
    } catch (std::exception &e) {
        return -1;
    }
    return 0;
}