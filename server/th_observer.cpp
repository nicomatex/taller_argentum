#include "th_observer.h"

ThObserver::ThObserver(Map& map, ThEventHandler& handler)
    : Thread(), map(map), handler(handler) {}

void ThObserver::run() {
    // while (running) {
    // std::unordered_map<unsigned int, position_t> u_map =
    // map.get_position_map();
    // handler.push(Event(u_map))
    // }
}

ThObserver::~ThObserver() {}
