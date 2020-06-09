#include "game_client.h"


bool debug = true;

int main(void){
    GameClient game("ind/textures.json","ind/sprites.json");
    game.run();
    return 0;
}