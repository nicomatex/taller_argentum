#ifndef __RECEIVE_HANDLER_H
#define __RECEIVE_HANDLER_H

#include "../include/blocking_th_event_handler.h"
#include "engine/ECS/entity_manager.h"
#include "engine/map.h"

class ClientReceiveHandler : public BlockingThEventHandler {
    EntityManager &entity_manager;

   private:
    Map &map;

    void handle(Event &ev) override;
    void handle_new_map(Event &ev);
    //la idea es tener los handlers todos aca
    
   public:
    ClientReceiveHandler(EntityManager &entity_manager, Map &map);
};

#endif