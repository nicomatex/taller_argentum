#include "th_client_receiver.h"

#include <iostream>

#include "socket_exception.h"

ThClientReceiver::ThClientReceiver(Socket& socket,
                                   ReceiveHandler<std::string>& receiver)
    : Thread(), socket(socket), protocol(this->socket), receiver(receiver) {}

// ThClientReceiver::ThClientReceiver(ThClientReceiver&& other)
//     : Thread(std::move(other)),
//       socket(other.socket),
//       receiver(other.receiver) {}
// ThClientReceiver& ThClientReceiver::operator=(ThClientReceiver&& other) {
//     Thread::operator=(std::move(other));
//     socket = std::move(other.socket);
//     receiver = std::move(other.receiver);
// }

void ThClientReceiver::run() {
    while (socket.is_connected()) {
        try {
            std::string str;
            protocol >> str;
            receiver.recieve(str);
        } catch (const ConnectionClosedSocketException& e) {
            receiver.close_queue();
            break;
        } catch (const ClosedBlockingQueueException& e) {
            break;
        }
    }
}

ThClientReceiver::~ThClientReceiver() {}
