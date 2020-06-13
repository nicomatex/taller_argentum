#ifndef TH_SOCKET_RECEIVER
#define TH_SOCKET_RECEIVER

#include <atomic>
#include <condition_variable>
#include <mutex>

#include "blocking_queue.h"
#include "protocol.h"
#include "socket.h"
#include "th_event_handler.h"
#include "thread.h"

class ThSocketReceiver : public Thread {
   private:
    std::atomic<bool> running;
    Protocol protocol;
    ThEventHandler* recieve_handler;
    std::mutex mutex;
    std::condition_variable cond_var;

   public:
    ThSocketReceiver(Socket& socket, ThEventHandler* recieve_handler);

    ThSocketReceiver(ThSocketReceiver&& other);
    ThSocketReceiver& operator=(ThSocketReceiver&& other);

    void assign_handler(ThEventHandler* receive_handler);

    virtual void run() override;

    void stop();

    ~ThSocketReceiver();
};

#endif  // TH_SOCKET_RECEIVER
