#include "chat_buffer.h"

ChatBuffer::ChatBuffer() {}

ChatBuffer::~ChatBuffer() {}

void ChatBuffer::push(std::string message) {
    std::unique_lock<std::mutex> l(m);
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;

    while((pos = message.find('\n',prev)) != std::string::npos){
        buffer.push(message.substr(prev, pos - prev));
        prev = pos + 1;
    }

    buffer.push(message.substr(prev));
}

void ChatBuffer::flush(Chat &chat) {
    std::unique_lock<std::mutex> l(m);
    while (!buffer.empty()) {
        chat.print_line(buffer.front());
        buffer.pop();
    }
}