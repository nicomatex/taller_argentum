#include "blocking_th_event_handler.h"

// Temp
#include <iostream>

#include "nlohmann/json.hpp"

Event BlockingThEventHandler::pop_event() {
    try {
        return event_queue.pop();
    } catch (ClosedBlockingQueueException& e) {
        throw EventHandlerStoppedException();
    }
}

BlockingThEventHandler::BlockingThEventHandler() : Thread() {}

BlockingThEventHandler::BlockingThEventHandler(BlockingThEventHandler&& other)
    : event_queue(std::move(other.event_queue)) {}
BlockingThEventHandler& BlockingThEventHandler::operator=(
    BlockingThEventHandler&& other) {
    event_queue = std::move(other.event_queue);
    return *this;
}

void BlockingThEventHandler::push_event(const Event& ev) {
    try {
        event_queue.push(ev);
    } catch (const ClosedBlockingQueueException& e) {
        throw EventHandlerStoppedException();
    }
}

void BlockingThEventHandler::run() {
    try {
        while (!event_queue.is_closed()) {
            Event ev = pop_event();
            try {
                handle(ev);
            } catch (const nlohmann::detail::exception& e) {
                std::cerr << "BlockingThEvHandler: error in json: "
                          << ev.get_json() << std::endl;
                continue;
            } catch (const EventHandlerStoppedException& e) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "BlockingThEvHandler: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "BlockingThEvHandler: Unknown exception" << std::endl;
    }
}

void BlockingThEventHandler::stop() {
    event_queue.close();
}

BlockingThEventHandler::~BlockingThEventHandler() {}
