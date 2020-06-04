#ifndef __TIMER_H
#define __TIMER_H
#include <cstdint>

class SDLTimer{
    private:
        bool _is_started;
        bool _is_paused;

        uint32_t start_ticks;
        uint32_t pause_ticks;
    public:
        SDLTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        uint32_t get_ticks();
        bool is_started();
        bool is_paused();
};

#endif