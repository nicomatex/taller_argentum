#ifndef __CHAR_CREATION_BUTTON_H
#define __CHAR_CREATION_BUTTON_H
#include "../../engine/UI/button.h"
#include "../../../include/network/socket_manager.h"

class RequestCharacterCreationButton : public Button {
   private:
    SocketManager& socket_manager;

   public:
    RequestCharacterCreationButton(SDL_Rect button_area, SDL_Rect viewport,
                                   SDL_Renderer* renderer,
                                   SocketManager& socket_manager);

    void on_click() override;
};

#endif