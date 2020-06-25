#ifndef __RECEIVE_HANDLER_H
#define __RECEIVE_HANDLER_H

#include <atomic>

#include "../include/blocking_th_event_handler.h"
#include "chat_buffer.h"
#include "engine/ECS/entity_manager.h"
#include "engine/map.h"
#include "game_state_monitor.h"
#include "map_change_buffer.h"

class ClientReceiveHandler : public BlockingThEventHandler {
   private:
    void handle(Event &ev) override;
    void handle_move(Event &ev);
    void handle_initialization(Event &ev);
    void handle_entity_update(Event &ev);
    void handle_chat_message(Event &ev);

    MapChangeBuffer &map_change_buffer;
    ChatBuffer &chat_buffer;
    GameStateMonitor &game_state_monitor;

    // la idea es tener los handlers todos aca

   public:
    ClientReceiveHandler(MapChangeBuffer &map_change_buffer,
                         ChatBuffer &chat_buffer,
                         GameStateMonitor &game_state_monitor);
    ~ClientReceiveHandler();
};

#endif