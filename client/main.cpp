#include "game_client.h"
#include <iostream>

bool debug = true;

int main(void){
    GameClient game("ind/textures.json","ind/sprites.json");
    game.run();
    std::cout << "ejecucion terminada" << std::endl;
    return 0;
}