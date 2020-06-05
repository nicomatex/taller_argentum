#include <iostream>

#include "../include/blocking_queue.h"
#include "../include/receive_handler.h"

class StrReceiveServerHandler : public ReceiveHandler<std::string> {
   private:
    BlockingQueue<std::string>& send_queue;

   public:
    StrReceiveServerHandler(BlockingQueue<std::string>& send_queue)
        : ReceiveHandler<std::string>(), send_queue(send_queue) {}

    virtual void handle_event(std::string& str) override {
        std::cout << "The Server got: " << str << std::endl;
        send_queue.push(str);
    }

    ~StrReceiveServerHandler() {}
};
