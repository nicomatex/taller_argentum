#ifndef __THREAD_H__
#define __THREAD_H__

#include <unistd.h>

#include <chrono>
#include <thread>

class Thread {
   private:
    bool runing;
    std::thread thread;

   public:
    // Create a guarded Thread
    Thread();

    // Thread cannot be copied
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    // Move Constructor
    Thread(Thread&& other);
    virtual Thread& operator=(Thread&& other);

    // Functor for starting the thread
    void operator()();

    // Start the thread
    void start();

    // Join the thread
    void join();

    // Sleeps for value in us
    void usleep(unsigned int us);

    template <class Rep, class Period>
    void sleep(const std::chrono::duration<Rep, Period>& duration) {
        std::this_thread::sleep_for(duration);
    }

    // Implemented by children
    virtual void run() = 0;

    // Deletes safely the thread, if it not joined, join()
    virtual ~Thread();
};

#endif  //__THREAD_H__
