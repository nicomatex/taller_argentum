#include "thread.h"

#include <iostream>
#include <utility>
static void _usleep(unsigned int us) {
    usleep(us);
}

Thread::Thread() : runing(false) {}

void Thread::operator()() {
    start();
}

void Thread::start() {
    if (runing)
        return;
    thread = std::thread(&Thread::run, this);
    runing = true;
}

void Thread::join() {
    thread.join();
    runing = false;
}

void Thread::usleep(unsigned int us) {
    _usleep(us);
}

Thread::Thread(Thread&& other) {
    thread = std::move(other.thread);
    runing = other.runing;
    other.runing = false;
}

Thread& Thread::operator=(Thread&& other) {
    thread = std::move(other.thread);
    runing = other.runing;
    other.runing = false;
    return *this;
}

Thread::~Thread() {
    if (runing && thread.joinable())
        thread.join();
}
