#include "th_event_handler.h"

Command ThEventHandler::pop_event() {
    try {
        return event_queue.pop();
    } catch (ClosedBlockingQueueException& e) {
        throw EventHandlerStoppedException();
    }
}

ThEventHandler::ThEventHandler() : Thread() {}

ThEventHandler::ThEventHandler(ThEventHandler&& other)
    : event_queue(std::move(other.event_queue)) {}
ThEventHandler& ThEventHandler::operator=(ThEventHandler&& other) {
    event_queue = std::move(other.event_queue);
    return *this;
}

void ThEventHandler::push_event(const Command& ev) {
    try {
        event_queue.push(ev);
    } catch (const ClosedBlockingQueueException& e) {
        throw EventHandlerStoppedException();
    }
}

void ThEventHandler::run() {
    while (!event_queue.is_closed()) {
        try {
            Command ev = pop_event();
            handle(ev);
        } catch (const EventHandlerStoppedException& e) {
            break;
        }
    }
}

void ThEventHandler::stop() {
    event_queue.close();
}

ThEventHandler::~ThEventHandler() {}
