#ifndef RECEIVE_HANDLER_H
#define RECEIVE_HANDLER_H

#include "blocking_queue.h"
#include "thread.h"

template <typename T>
class ReceiveHandler : public Thread {
   private:
    BlockingQueue<T> event_queue;

   public:
    ReceiveHandler() {}

    ReceiveHandler(ReceiveHandler<T>&& other)
        : event_queue(std::move(other.event_queue)) {}
    ReceiveHandler& operator=(ReceiveHandler<T>&& other) {
        event_queue = std::move(other.event_queue);
    }

    void recieve(T t) {
        event_queue.push(t);
    }

    virtual void run() override {
        while (!event_queue.is_closed()) {
            try {
                T t(event_queue.pop());
                handle_event(t);
            } catch (const ClosedBlockingQueueException& e) {
                break;
            }
        }
    }

    void close_queue() {
        event_queue.close();
    }

    virtual void handle_event(T& t) = 0;

    ~ReceiveHandler() {}
};

#endif  // RECEIVE_HANDLER_H
