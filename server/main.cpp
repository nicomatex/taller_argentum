#include <iostream>
#include <stdexcept>

#include "game_server.h"

int main(const int argc, const char* argv[]) try {
    GameServer server;
    server.run();
    return 0;
} catch (const std::exception& e) {
    std::cerr << "ServerMain: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "ServerMain: Unknown exception" << std::endl;
}
