#ifndef TH_OBSERVER_H
#define TH_OBSERVER_H

#include <atomic>

#include "../include/blocking_th_event_handler.h"
#include "../include/thread.h"
#include "../include/types.h"
#include "map_monitor.h"

class ThObserver : public Thread {
   private:
    std::atomic<bool> running;
    MapMonitor& map;
    BlockingThEventHandler& handler;

   public:
    ThObserver(MapMonitor& map_monitor, BlockingThEventHandler& handler);

    void run() override;

    void stop();

    ~ThObserver();
};

#endif  // TH_OBSERVER_H
