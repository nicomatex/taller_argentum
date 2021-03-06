#ifndef CREATION_HANDLER_H
#define CREATION_HANDLER_H

#include "../../include/blocking_th_event_handler.h"
#include "../../include/event.h"

class CreationHandler : public BlockingThEventHandler {
   private:
    void disconnect(Event& event) const;

   protected:
    void handle(Event& ev) override;

   public:
    CreationHandler();
};

#endif  // CREATION_HANDLER_H