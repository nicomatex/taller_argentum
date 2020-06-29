#include "chat_buffer.h"

ChatBuffer::ChatBuffer() {}

ChatBuffer::~ChatBuffer() {}

void ChatBuffer::push(std::string message) {
    std::unique_lock<std::mutex> l(m);
    buffer.push(message);
}

void ChatBuffer::flush(Chat &chat) {
    std::unique_lock<std::mutex> l(m);
    while (!buffer.empty()) {
        chat.print_line(buffer.front());
        buffer.pop();
    }
}