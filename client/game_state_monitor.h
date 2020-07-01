#ifndef __GAME_STATE_MONITOR_H
#define __GAME_STATE_MONITOR_H

#include <condition_variable>
#include <mutex>


typedef enum{
    LOGGING,WAITING_FOR_INITIALIZATION,READY_TO_RUN,RUNNING,SWITCHING_MAPS,EXITING
}game_state_t;

class GameStateMonitor {
   private:
    std::mutex m;
    bool connected;
    game_state_t game_state;
    std::condition_variable cv;

   public:
    GameStateMonitor();
    ~GameStateMonitor();

    bool is_connected();
    

    void set_connected_status(bool new_connection_status);
    
    void set_game_state(game_state_t new_game_state);
    game_state_t get_game_state();

    /* Duerme el thread llamante hasta que el estado del juego 
    sea el esperado. */
    void wait_for_game_state(game_state_t expected_game_state);

    void quit();
};

#endif