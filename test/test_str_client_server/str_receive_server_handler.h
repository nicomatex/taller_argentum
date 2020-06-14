#include <iostream>
#include <map>
#include <unordered_set>

#include "../include/blocking_th_event_handler.h"
#include "../include/event.h"

class StrReceiveServerHandler : public BlockingThEventHandler {
   private:
    BlockingThEventHandler& sender;

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
    StrReceiveServerHandler(BlockingThEventHandler& sender)
        : BlockingThEventHandler(), sender(sender) {}

    ~StrReceiveServerHandler() {}
};
