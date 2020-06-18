#ifndef __UI_EVENT_HANDLER_H
#define __UI_EVENT_HANDLER_H

#include <atomic>

#include "../include/thread.h"
#include "../include/socket_manager.h"
#include "event_factory.h"

class UiEventHandler{
   private:
    EventFactory event_factory;
    std::atomic_bool &running;
    SocketManager &socket_manager;

   public:
    UiEventHandler(std::atomic_bool &running, SocketManager &socket_manager);
    void handle_keydown_move_up();
    void handle_keydown_move_down();
    void handle_keydown_move_left();
    void handle_keydown_move_right();
    
    void handle_keyup_move_up();
    void handle_keyup_move_down();
    void handle_keyup_move_left();
    void handle_keyup_move_right();
    void handle();
};

#endif