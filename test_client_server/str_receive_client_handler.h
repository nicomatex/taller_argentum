#include <iostream>

#include "../include/receive_handler.h"

class StrReceiveClientHandler : public ReceiveHandler<std::string> {
   public:
    StrReceiveClientHandler() : ReceiveHandler<std::string>() {}

    virtual void handle_event(std::string& str) override {
        std::cout << "The Client got: " << str << std::endl;
    }

    ~StrReceiveClientHandler() {}
};
