#include <sys/stat.h>

#include <fstream>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "client_config.h"
#include "game_client.h"

bool debug = true;

using json = nlohmann::json;

int main(void) {
    json config;
    std::ifstream config_file(CONFIG_FILE);
    //Si no se encuentra el archivo de configs en este directorio, se asume 
    //que el juego esta instalado mediante paquete.
    if (!config_file.is_open()) {
        const char* env_home = std::getenv("HOME");
        std::string config_file_path = env_home;
        config_file_path += "/argentum/";
        std::string config_file_name = config_file_path + CONFIG_FILE;

        config_file.open(config_file_name);
        if (!config_file.is_open()) {
            struct stat sb;
            if (!(stat(config_file_path.c_str(), &sb) == 0 &&
                  S_ISDIR(sb.st_mode))) {
                if (mkdir(config_file_path.c_str(), 0777) == -1) {
                    std::cerr << "Config file couldn't be located nor created."
                              << std::endl;
                    return -1;
                }
            }
            std::cout << "Config file not found. Creating one..." << std::endl;
            std::ofstream new_conf_file(config_file_name);
            new_conf_file << BASE_CONFIG_FILE << std::endl;
            new_conf_file.close();
            config_file.open(config_file_name);
        }
        if (chdir("/usr/local/share/argentum") < 0) {
            std::cerr
                << "Game files not found. Is the game installed correctly?"
                << std::endl;
            return -1;
        }
    }
    config = json::parse(config_file);

    try {
        GameClient game(config);
        game.run();
    } catch (std::exception &e) {
        return -1;
    }
    return 0;
}