#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <atomic>

#include "../../include/thread.h"
#include "../map_manager.h"

class GameLoop : public Thread {
   private:
    std::atomic_bool running;
    MapManager& map_manager;

   public:
    GameLoop(MapManager& map_manager);
    void run() override;
    void stop();
    ~GameLoop();
};
#endif  // GAME_LOOP_H
