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

bool BlockingThEventHandler::is_threaded() const {
    return true;
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
        while (!event_queue.is_closed() || !event_queue.is_empty()) {
            Event ev = pop_event();
            handle(ev);
        }
    } catch (const EventHandlerStoppedException& e) {
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
