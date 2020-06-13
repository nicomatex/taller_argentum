#include "th_dispatcher.h"

// Temp
#include <iostream>

ThDispatcher::ThDispatcher(BlockingQueue<Event>& queue) : game_queue(queue) {}

void ThDispatcher::handle(Event& ev) {
    std::cerr << "Dispatcher: Pushing event: " << ev.get_json() << std::endl;
    game_queue.push(ev);
}

ThDispatcher::~ThDispatcher() {}
