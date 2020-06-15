#include "socket_manager.h"

#include "my_exception.h"

// Temp
#include <iostream>

SocketManager::SocketManager(int id, Socket socket,
                             BlockingThEventHandler& receive_handler)
    : client_id(id),
      socket(std::move(socket)),
      receiver(id, this->socket, receive_handler),
      sender(this->socket) {}
SocketManager::SocketManager(Socket& socket,
                             BlockingThEventHandler& receive_handler)
    : client_id(0),
      socket(std::move(socket)),
      receiver(client_id, this->socket, receive_handler),
      sender(this->socket) {}

void SocketManager::start() {
    receiver.start();
    sender.start();
}

void SocketManager::send(const Event& ev) {
    sender.push_event(ev);
}

int SocketManager::get_id() const {
    return client_id;
}

bool SocketManager::is_done() const {
    return !socket.is_connected();
}

void SocketManager::stop(bool shutdown) {
    sender.stop();
    receiver.stop();
    if (shutdown)
        socket.shutdown_and_close();
}

void SocketManager::join() {
    sender.join();
    std::cerr << "Sender joined\n";
    receiver.join();
    std::cerr << "Receiver joined\n";
}

SocketManager::~SocketManager() {}
