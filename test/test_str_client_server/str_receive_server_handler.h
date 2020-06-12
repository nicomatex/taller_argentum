#include <iostream>
#include <map>
#include <unordered_set>

#include "../include/event.h"
#include "../include/th_event_handler.h"

class StrReceiveServerHandler : public ThEventHandler {
   private:
    ThEventHandler& sender;

   protected:
    virtual void handle(Event& ev) override {
        std::cout << "The Server got: ";
        std::cout << ev.get_json().dump();
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
