#include <iostream>

#include "../include/command.h"
#include "../include/th_event_handler.h"

class StrReceiveClientHandler : public ThEventHandler {
   protected:
    virtual void handle(Command& ev) override {
        std::cout << "The Client got: ";
        ev.execute(std::cout);
        std::cout << std::endl;
    }

   public:
    StrReceiveClientHandler() : ThEventHandler() {}

    ~StrReceiveClientHandler() {}
};
