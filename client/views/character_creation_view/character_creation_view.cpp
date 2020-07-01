#include "character_creation_view.h"
#include "../../client_config.h"
#include "../../engine/resource_manager.h"

CharacterCreationView::CharacterCreationView(SDLWindow &window, ResponsiveScaler &scaler,
                     GameStateMonitor &game_state_monitor,
                     SocketManager &socket_manager)
    : window(window),
      scaler(scaler),
      background(ResourceManager::get_instance().get_texture("interface", 3)),
      game_state_monitor(game_state_monitor){
    window.set_viewport(scaler.scale(CHAR_CREATION_VIEWPORT));
}


CharacterCreationView::~CharacterCreationView(){}

void CharacterCreationView::run(){
    while(game_state_monitor.get_game_state() == CREATING_CHARACTER){
        window.fill(0,0,0,255);
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                game_state_monitor.quit();
            }
        }
        background.render(scaler.scale(CHAR_CREATION_BACKGROUND_AREA));
        window.render();
    }
}