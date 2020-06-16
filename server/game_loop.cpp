#include "game_loop.h"

#include <iostream>

constexpr std::chrono::milliseconds TIME_STEP(15);

GameLoop::GameLoop(MapManager& map_manager)
    : running(true), map_manager(map_manager) {}

GameLoop::~GameLoop() {}

void GameLoop::run() {
    try {
        while (running) {
            auto start = std::chrono::steady_clock::now();
            map_manager.update(TIME_STEP.count());
            sleep(TIME_STEP - (std::chrono::steady_clock::now() - start));
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void GameLoop::stop() {
    running = false;
}
