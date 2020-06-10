#include <iostream>
#include <map>
#include <unordered_set>

#include "../include/command.h"
#include "../include/th_event_handler.h"

class StrReceiveServerHandler : public ThEventHandler {
   private:
    ThEventHandler& sender;

   protected:
    virtual void handle(Command& ev) override {
        std::cout << "The Server got: ";
        ev.execute(std::cout);
        std::cout << std::endl;
        try {
            sender.push_event(ev);
        } catch (const EventHandlerStoppedException& e) {
            stop();
        }
    }

   public:
    StrReceiveServerHandler(ThEventHandler& sender)
        : ThEventHandler(), sender(sender) {}

    ~StrReceiveServerHandler() {}
};
