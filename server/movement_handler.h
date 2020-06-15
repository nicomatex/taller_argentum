#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "th_event_handler.h"
#include "server_manager.h"


#ifndef MOVEMENT_ACTION_T       	 //TODO: PONER EN  DISTINTOS HEADERS 
#define MOVEMENT_ACTION_T      		 // Y HACER INCLUDES, ESTO ES RE FEO, IDEM
enum mov_action_t { START, STOP };   // EN LADO CLIENTE PARA NICO
#endif

#ifndef DIRECTION_T
#define DIRECTION_T
enum direction_t { UP, DOWN, LEFT, RIGHT };
#endif

class MovementHandler : public ThEventHandler {
   protected:
    void run_handler() override;
   public:
    MovementHandler(Event ev, ServerManager& server_manager);
    ~MovementHandler();
}

#endif // MOVEMENT_HANDLER_H