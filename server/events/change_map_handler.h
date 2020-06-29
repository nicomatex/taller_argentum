#ifndef CHANGE_MAP_HANDLER_H
#define CHANGE_MAP_HANDLER_H

#include "th_event_handler.h"

class ChangeMapHandler : public ThEventHandler {
   protected:
    void run_handler() override;

   public:
    ChangeMapHandler(Event ev);
    ~ChangeMapHandler();
};

#endif  // CHANGE_MAP_HANDLER_H
