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
    /**
     * @brief Construct a new Thread object.
     *
     */
    Thread();

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    /**
     * @brief Move constructor.
     *
     * @param other
     */
    Thread(Thread&& other);
    virtual Thread& operator=(Thread&& other);

    /**
     * @brief Thread as a functor, same as start().
     *
     */
    void operator()();

    /**
     * @brief Start the thread.
     *
     */
    void start();

    /**
     * @brief Join the thread.
     *
     */
    virtual void join();

    /**
     * @brief  Sleeps for value in micro-seconds.
     *
     * @param us
     */
    void usleep(unsigned int us);

    /**
     * @brief Wrapper of std::this_thread::sleep_for
     *
     * @tparam Rep
     * @tparam Period
     * @param duration
     */
    template <class Rep, class Period>
    void sleep(const std::chrono::duration<Rep, Period>& duration) {
        std::this_thread::sleep_for(duration);
    }

    /**
     * @brief Function to be called by the thread.
     *
     */
    virtual void run() = 0;

    /**
     * @brief Deletes safely the thread, if it not joined, join()
     *
     */
    virtual ~Thread();
};

#endif  //__THREAD_H__
