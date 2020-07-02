#ifndef CHANGE_MAP_HANDLER_H
#define CHANGE_MAP_HANDLER_H

#include "../../include/blocking_th_event_handler.h"

class ChangeMapHandler : public BlockingThEventHandler {
   protected:
    void handle(Event& ev) override;

   public:
    ChangeMapHandler();
    ~ChangeMapHandler();
};

#endif  // CHANGE_MAP_HANDLER_H
