#include "game_client.h"
#include "client_config.h"
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>

bool debug = true;

using json = nlohmann::json;

int main(void){
    json config;
    try{
        std::ifstream config_file(CLIENT_CONFIG_FILE);
        config = json::parse(config_file);
    }catch(std::exception &e){
        std::cerr << MSG_ERR_CONFIG_FILE << std::endl;
        return 1;
    }
    GameClient game(config);
    game.run();
    return 0;
}