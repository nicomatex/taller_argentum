#include "game_state_monitor.h"

GameStateMonitor::GameStateMonitor()
    : game_state(LOGGING),
      login_state(FIRST_LOGIN),
      char_creation_state(FIRST_TRY) {}

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

void GameStateMonitor::set_login_state(login_state_t new_login_state) {
    std::unique_lock<std::mutex> l(m);
    login_state = new_login_state;
}

void GameStateMonitor::set_char_creation_state(
    char_creation_state_t new_char_creation_state) {
    std::unique_lock<std::mutex> l(m);
    char_creation_state = new_char_creation_state;
}

login_state_t GameStateMonitor::get_login_state() {
    std::unique_lock<std::mutex> l(m);
    return login_state;
}

char_creation_state_t GameStateMonitor::get_char_creation_state() {
    std::unique_lock<std::mutex> l(m);
    return char_creation_state;
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
        if (!connected) {
            return;
        }
        cv.wait(l);
    }
}

void GameStateMonitor::wait_for_next_game_state() {
    std::unique_lock<std::mutex> l(m);
    cv.wait(l);
}

game_state_t GameStateMonitor::get_game_state() {
    std::unique_lock<std::mutex> l(m);
    return game_state;
}