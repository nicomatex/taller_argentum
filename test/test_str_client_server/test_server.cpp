#include <iostream>

#include "../server/th_client_accepter.h"

int main(const int argc, const char* argv[]) try {
    ThClientAccepter accepter(Socket("2500", 10));
    accepter.start();

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "q" || line == "quit")
            break;
    }
    accepter.stop();
    accepter.join();

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unknown exception" << std::endl;
}
