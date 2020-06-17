#ifndef TH_SOCKET_RECEIVER
#define TH_SOCKET_RECEIVER

#include <atomic>
#include <condition_variable>
#include <mutex>

#include "blocking_queue.h"
#include "blocking_th_event_handler.h"
#include "protocol.h"
#include "socket.h"
#include "thread.h"
#include "types.h"

class ThSocketReceiver : public Thread {
   private:
    std::atomic<bool> running;
    ClientId client_id;
    Protocol protocol;
    BlockingThEventHandler& recieve_handler;

   public:
    ThSocketReceiver(int id, Socket& socket,
                     BlockingThEventHandler& recieve_handler);

    ThSocketReceiver(ThSocketReceiver&& other);
    ThSocketReceiver& operator=(ThSocketReceiver&& other) = delete;

    virtual void run() override;

    void stop();

    ~ThSocketReceiver();
};

#endif  // TH_SOCKET_RECEIVER
