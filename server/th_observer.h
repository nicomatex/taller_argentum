#ifndef TH_OBSERVER_H
#define TH_OBSERVER_H

#include <atomic>

#include "../include/blocking_th_event_handler.h"
#include "../include/thread.h"
#include "map.h"

class ThObserver : public Thread {
   private:
    std::atomic<bool> running;
    Map& map;
    BlockingThEventHandler& handler;

   public:
    ThObserver(Map& map, BlockingThEventHandler& handler);

    void run() override;

    ~ThObserver();
};

#endif  // TH_OBSERVER_H
