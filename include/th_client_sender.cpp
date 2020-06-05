#include "th_client_sender.h"

#include <iostream>

#include "socket_exception.h"

ThClientSender::ThClientSender(Socket& socket,
                               BlockingQueue<std::string>& queue)
    : Thread(), socket(socket), protocol(this->socket), input_queue(queue) {}

// ThClientSender::ThClientSender(ThClientSender&& other)
//     : Thread(std::move(other)),
//       socket(other.socket),
//       protocol(other.protocol),
//       input_queue(other.input_queue) {}
// ThClientSender& ThClientSender::operator=(ThClientSender&& other) {
//     Thread::operator=(std::move(other));
//     socket = std::move(other.socket);
//     input_queue = other.input_queue;
// }

void ThClientSender::run() {
    while (!input_queue.is_closed() && socket.is_connected()) {
        try {
            std::string str;
            str = input_queue.pop();
            protocol << str;
        } catch (const ClosedBlockingQueueException& e) {
            break;
        } catch (const ConnectionClosedSocketException& e) {
            break;
        }
    }
    socket.shutdown_and_close();
}

ThClientSender::~ThClientSender() {}
