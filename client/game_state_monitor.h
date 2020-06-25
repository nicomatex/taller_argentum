#ifndef __GAME_STATE_MONITOR_H
#define __GAME_STATE_MONITOR_H

#include <mutex>

class GameStateMonitor{
    private:
        std::mutex m;
        bool connected;
        bool game_running;
    
    public:
        GameStateMonitor();
        ~GameStateMonitor();

        bool is_connected();
        bool is_running();

        void set_connected_status(bool new_connection_status);
        void set_running_status(bool new_running_status);

        void quit();
};

#endif