#include "game_state_monitor.h"


GameStateMonitor::GameStateMonitor(){}

GameStateMonitor::~GameStateMonitor(){}

bool GameStateMonitor::is_connected(){
    std::unique_lock<std::mutex> l(m);
    return connected;
}

bool GameStateMonitor::is_running(){
    std::unique_lock<std::mutex> l(m);
    return game_running;
}

void GameStateMonitor::set_connected_status(bool new_connected_status){
    std::unique_lock<std::mutex> l(m);
    connected = new_connected_status;
}

void GameStateMonitor::set_running_status(bool new_running_status){
    std::unique_lock<std::mutex> l(m);
    game_running = new_running_status;
}


void GameStateMonitor::quit(){
    std::unique_lock<std::mutex> l(m);
    game_running = false;
    connected = false;
}