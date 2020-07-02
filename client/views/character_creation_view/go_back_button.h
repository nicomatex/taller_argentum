#ifndef __GO_BACK_BUTTON_H
#define __GO_BACK_BUTTON_H
#include "../../engine/UI/button.h"
#include "../../game_state_monitor.h"

class GoBackButton : public Button{
    private:
        GameStateMonitor& game_state_monitor;
        
    public:
        GoBackButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
                GameStateMonitor& game_state_monitor);
        
        void on_click() override;
};

#endif