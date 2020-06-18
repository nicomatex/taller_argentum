#ifndef __RECEIVE_HANDLER_H
#define __RECEIVE_HANDLER_H

#include "../include/blocking_th_event_handler.h"
#include "engine/ECS/entity_manager.h"
#include "engine/map.h"
#include <atomic>

class ClientReceiveHandler : public BlockingThEventHandler {
    EntityManager &entity_manager;
    std::atomic_bool &ready;
    std::atomic_bool &running;
    
   private:
    Map &map;

    void handle(Event &ev) override;
    void handle_new_map(Event &ev);
    void handle_move(Event &ev);
    //la idea es tener los handlers todos aca
    
   public:
    ClientReceiveHandler(EntityManager &entity_manager, Map &map, std::atomic_bool& ready, std::atomic_bool& running);
};

#endif