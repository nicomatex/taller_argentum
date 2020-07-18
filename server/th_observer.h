#ifndef TH_OBSERVER_H
#define TH_OBSERVER_H

#include <atomic>

#include "../include/blocking_th_event_handler.h"
#include "../include/thread.h"
#include "../include/types.h"
#include "game/map_monitor.h"

class ThObserver : public Thread {
   private:
    std::atomic_bool running;
    MapMonitor& map;
    BlockingThEventHandler& handler;
    std::atomic_bool forced_update;

    void send_update_logs();

   public:
    ThObserver(MapMonitor& map_monitor, BlockingThEventHandler& handler);

    void run() override;

    void stop();

    ~ThObserver();
};

#endif  // TH_OBSERVER_H
