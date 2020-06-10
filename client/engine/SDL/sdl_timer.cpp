#include "sdl_timer.h"
#include "SDL2/SDL.h"
#include <utility>

SDLTimer::SDLTimer()
    : start_ticks(0), pause_ticks(0), _is_paused(false), _is_started(false) {}

SDLTimer::SDLTimer(const SDLTimer &other)
    : start_ticks(other.start_ticks),
      pause_ticks(other.pause_ticks),
      _is_paused(other._is_paused),
      _is_started(other._is_started) {}

SDLTimer& SDLTimer::operator=(const SDLTimer &other){
    this->start_ticks = other.start_ticks;
    this->pause_ticks = other.pause_ticks;
    this->_is_paused = other._is_paused;
    this->_is_started = other._is_started;
    return *this;
}

SDLTimer::SDLTimer(SDLTimer &&other){
    this->start_ticks = std::move(other.start_ticks);
    this->pause_ticks = std::move(other.pause_ticks);
    this->_is_paused = std::move(other._is_paused);
    this->_is_started = std::move(other._is_started);
}

SDLTimer& SDLTimer::operator=(SDLTimer &&other){
    this->start_ticks = std::move(other.start_ticks);
    this->pause_ticks = std::move(other.pause_ticks);
    this->_is_paused = std::move(other._is_paused);
    this->_is_started = std::move(other._is_started);
    return *this;
}

SDLTimer::~SDLTimer() {}

void SDLTimer::start() {
    _is_started = true;
    _is_paused = false;

    start_ticks = SDL_GetTicks();
    pause_ticks = 0;
}

void SDLTimer::stop() {
    _is_started = false;
    _is_paused = false;
    start_ticks = 0;
    pause_ticks = 0;
}

void SDLTimer::pause() {
    if (_is_started && !_is_paused) {
        _is_paused = true;
        pause_ticks = SDL_GetTicks() - start_ticks;
        start_ticks = 0;
    }
}

void SDLTimer::unpause() {
    if (_is_started && _is_paused) {
        _is_paused = false;
        start_ticks = SDL_GetTicks() - pause_ticks;
        pause_ticks = 0;
    }
}

uint32_t SDLTimer::get_ticks() const {
    uint32_t time = 0;
    if (_is_started) {
        time = _is_paused ? pause_ticks : SDL_GetTicks() - start_ticks;
    }
    return time;
}

bool SDLTimer::is_started() const { return _is_started; }

bool SDLTimer::is_paused() const { return _is_paused; }