#ifndef __GAME_STATE_MONITOR_H
#define __GAME_STATE_MONITOR_H

#include <mutex>
#include <condition_variable>

class GameStateMonitor{
    private:
        std::mutex m;
        bool connected;
        bool game_running;
        bool initialization_requested;
        std::condition_variable cv;

    public:
        GameStateMonitor();
        ~GameStateMonitor();

        bool is_connected();
        bool is_running();

        void set_connected_status(bool new_connection_status);
        void set_running_status(bool new_running_status);

        void wait_for_initialization_request();

        void set_initialization_requested(bool initialization_requested);
        void quit();
};

#endif