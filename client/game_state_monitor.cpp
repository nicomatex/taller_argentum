#include "game_state_monitor.h"

GameStateMonitor::GameStateMonitor() {}

GameStateMonitor::~GameStateMonitor() {}

bool GameStateMonitor::is_connected() {
    std::unique_lock<std::mutex> l(m);
    return connected;
}

void GameStateMonitor::set_connected_status(bool new_connected_status) {
    std::unique_lock<std::mutex> l(m);
    connected = new_connected_status;
    cv.notify_all();
}

void GameStateMonitor::set_game_state(game_state_t new_game_state) {
    std::unique_lock<std::mutex> l(m);
    game_state = new_game_state;
    cv.notify_all();
}

void GameStateMonitor::quit() {
    std::unique_lock<std::mutex> l(m);
    game_state = EXITING;
    connected = false;
    cv.notify_all();
}

void GameStateMonitor::wait_for_game_state(game_state_t expected_game_state) {
    std::unique_lock<std::mutex> l(m);
    while (game_state != expected_game_state) {
        if(!connected){
            return;
        }
        cv.wait(l);
    }
}

game_state_t GameStateMonitor::get_game_state(){
    std::unique_lock<std::mutex> l(m);
    return game_state;
}