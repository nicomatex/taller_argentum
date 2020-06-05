#include <iostream>

#include "../include/socket.h"
#include "../include/th_client_receiver.h"
#include "../include/th_client_sender.h"
#include "str_receive_client_handler.h"

int main(const int argc, const char* argv[]) try {
    Socket client("localhost", "2500");

    StrReceiveClientHandler str_handler;
    ThClientReceiver receiver(client, str_handler);

    BlockingQueue<std::string> str_queue;
    ThClientSender sender(client, str_queue);

    receiver.start();
    sender.start();
    str_handler();

    std::string line;
    while (std::getline(std::cin, line)) {
        str_queue.push(line);
    }
    str_queue.close();
    sender.join();
    std::cerr << "Sender joined\n";
    receiver.join();
    std::cerr << "Receiver joined\n";

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unknown exception" << std::endl;
}
