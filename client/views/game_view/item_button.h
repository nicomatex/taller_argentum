#ifndef __ITEM_BUTTON_H
#define __ITEM_BUTTON_H

#include "../../../include/network/socket_manager.h"
#include "../../engine/UI/button.h"
#include "../../engine/SDL/sdl_timer.h"

class ItemButton : public Button {
   private:
    int slot_number;
    SocketManager& socket_manager;
    SDLTimer double_click_timer;
    
   public:
    ItemButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
               SlotId slot_number, SocketManager& socket_manager);

    void on_click() override;
};

#endif