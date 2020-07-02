#ifndef __CREATE_CHARACTER_BUTTON
#define __CREATE_CHARACTER_BUTTON
#include "../../engine/UI/button.h"
#include "../../game_state_monitor.h"

class CreateCharacterButton : public Button{
    private:
        GameStateMonitor& game_state_monitor;
        
    public:
        CreateCharacterButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
                GameStateMonitor& game_state_monitor);
        
        void on_click() override;
};

#endif