#ifndef __CHAT_BUFFER_H
#define __CHAT_BUFFER_H

#include <mutex>
#include <queue>
#include <string>

#include "chat.h"

class ChatBuffer {
   private:
    std::mutex m;
    std::queue<std::string> buffer;

   public:
    ChatBuffer();
    ~ChatBuffer();

    void push(std::string message);
    void flush(Chat &chat);
};

#endif