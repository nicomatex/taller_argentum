#include <iostream>

#include "../include/blocking_th_event_handler.h"
#include "../include/event.h"

class StrReceiveClientHandler : public BlockingThEventHandler {
   protected:
    virtual void handle(Event& ev) override {
        std::cout << "The Client got: ";
        std::cout << ev.get_json().dump();
        std::cout << std::endl;
    }

   public:
    StrReceiveClientHandler() : BlockingThEventHandler() {}

    ~StrReceiveClientHandler() {}
};
