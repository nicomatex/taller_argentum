#include <iostream>

#include "../include/socket.h"
#include "../include/th_client_receiver.h"
#include "../include/th_client_sender.h"
#include "str_receive_server_handler.h"

int main(const int argc, const char* argv[]) try {
    Socket listener("2500", 10);
    Socket client = listener.accept();

    BlockingQueue<std::string> str_queue;
    ThClientSender sender(client, str_queue);

    StrReceiveServerHandler str_handler(str_queue);
    ThClientReceiver receiver(client, str_handler);

    receiver();
    sender();
    str_handler();

    receiver.join();
    str_handler.join();
    str_queue.close();
    sender.join();

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unknown exception" << std::endl;
}
