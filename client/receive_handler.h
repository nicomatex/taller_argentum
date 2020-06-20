#ifndef __RECEIVE_HANDLER_H
#define __RECEIVE_HANDLER_H

#include <atomic>
#include "../include/blocking_th_event_handler.h"
#include "engine/ECS/entity_manager.h"
#include "engine/map.h"
#include "map_change_buffer.h"

class ClientReceiveHandler : public BlockingThEventHandler {
   private:
    
    
    void handle(Event &ev) override;
    void handle_new_map(Event &ev);
    void handle_move(Event &ev);
    void handle_initialization(Event &ev);
    MapChangeBuffer &map_change_buffer;

    //la idea es tener los handlers todos aca
    
   public:
    ClientReceiveHandler(MapChangeBuffer &map_change_buffer);
    ~ClientReceiveHandler();
};

#endif