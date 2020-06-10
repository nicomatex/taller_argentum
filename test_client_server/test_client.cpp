#include <iostream>

#include "../include/command.h"
#include "../include/socket.h"
#include "../include/socket_manager.h"
#include "str_receive_client_handler.h"

int main(const int argc, const char* argv[]) try {
    Socket client("localhost", "2500");

    StrReceiveClientHandler str_handler;
    SocketManager socket_manager(client, &str_handler);

    socket_manager.start();
    str_handler.start();

    std::string line;
    while (std::getline(std::cin, line)) {
        socket_manager.send(Command(line));
    }
    socket_manager.stop(true);
    std::cerr << "Stopped Socket Manager\n";
    str_handler.stop();
    std::cerr << "Stopped Str Handler\n";

    socket_manager.join();
    str_handler.join();

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unknown exception" << std::endl;
}
