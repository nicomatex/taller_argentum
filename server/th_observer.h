#ifndef TH_OBSERVER_H
#define TH_OBSERVER_H

#include "../include/th_event_handler.h"
#include "../include/thread.h"
#include "map.h"

class ThObserver : public Thread {
   private:
    Map& map;
    ThEventHandler& handler;

   public:
    ThObserver(Map& map, ThEventHandler& handler);

    void run() override;

    ~ThObserver();
};

#endif  // TH_OBSERVER_H
