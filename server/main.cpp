#include "game_server.h"

int main(const int argc, const char* argv[]) try {
    GameServer server;
    server.run();
    return 0;
} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
} catch (...) {
    std::cerr << "Unknown exception" << std::endl;
    return 1;
}
