#ifndef __queue_BLOQUEANTE_H__
#define __queue_BLOQUEANTE_H__

#include <condition_variable>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <utility>

class ClosedBlockingQueueException : std::exception {
   public:
    ClosedBlockingQueueException() {}

    virtual const char* what() const noexcept {
        return "Se cerró la queue bloqueante";
    }

    ~ClosedBlockingQueueException() {}
};

template <typename T>
class BlockingQueue {
   private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond_var;
    bool _is_closed;
    bool wait_depleted;

    bool meets_deplete_cond() const {
        return wait_depleted ? queue.empty() : true;
    }

   public:
    BlockingQueue() : _is_closed(false), wait_depleted(false) {}

    BlockingQueue(const BlockingQueue<T>& other)
        : queue(other.queue), _is_closed(other._is_closed) {}

    BlockingQueue<T>& operator=(const BlockingQueue<T>& other) {
        queue = std::queue<T>(other.queue);
        _is_closed = other._is_closed;
        return *this;
    }

    BlockingQueue(BlockingQueue<T>&& other) {
        queue = std::move(other.queue);
        _is_closed = other._is_closed;
        other._is_closed = true;
    }

    bool is_empty() const {
        return queue.empty();
    }

    void push(T t) {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(t);
        cond_var.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        while (queue.empty()) {
            if (!_is_closed)
                cond_var.wait(lock);
            else
                throw ClosedBlockingQueueException();
        }
        // if (meets_deplete_cond())
        //     throw ClosedBlockingQueueException();
        T t = queue.front();
        queue.pop();
        return t;
    }

    void close(bool deplete = false) {
        std::unique_lock<std::mutex> lock(mutex);
        wait_depleted = deplete;
        _is_closed = true;
        cond_var.notify_all();
    }

    bool is_closed() const {
        return _is_closed && meets_deplete_cond();
    }

    ~BlockingQueue() {}
};

#endif  //__queue_BLOQUEANTE_H__
