#include "th_event_handler.h"

ThEventHandler::ThEventHandler(Event ev) : Thread(), running(true), event(ev) {}

bool ThEventHandler::is_done() {
    return running;
}

void ThEventHandler::run() {
    try {
        run_handler();
    } catch (const std::exception& e) {
        std::cerr << "EventHandler: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "EventHandler: Unknown exception" << std::endl;
    }
    running = false;
}

ThEventHandler::~ThEventHandler() {}
