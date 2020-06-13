#include "th_dispatcher.h"

ThDispatcher::ThDispatcher(BlockingQueue<Event>& queue) : game_queue(queue) {}

void ThDispatcher::handle(Event& ev) {
    game_queue.push(ev);
}

ThDispatcher::~ThDispatcher() {}
