#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include <atomic>
#include "../include/thread.h"

class GameLoop: public Thread{
    private:
        std::atomic_bool running;

    public:
        GameLoop();
        ~GameLoop();
        void run() override;
};
#endif  // GAME_LOOP_H
