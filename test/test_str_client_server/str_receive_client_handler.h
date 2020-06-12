#include <iostream>

#include "../include/event.h"
#include "../include/th_event_handler.h"

class StrReceiveClientHandler : public ThEventHandler {
   protected:
    virtual void handle(Event& ev) override {
        std::cout << "The Client got: ";
        std::cout << ev.get_json().dump();
        std::cout << std::endl;
    }

   public:
    StrReceiveClientHandler() : ThEventHandler() {}

    ~StrReceiveClientHandler() {}
};
