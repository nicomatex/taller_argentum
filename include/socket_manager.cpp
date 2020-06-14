#include "socket_manager.h"

#include "my_exception.h"

// Temp
#include <iostream>

SocketManager::SocketManager(int id, Socket socket)
    : id(id),
      socket(std::move(socket)),
      receiver(this->socket, nullptr),
      sender(this->socket) {}
SocketManager::SocketManager(Socket& socket,
                             BlockingThEventHandler* receive_handler)
    : id(0),
      socket(std::move(socket)),
      receiver(this->socket, receive_handler),
      sender(this->socket) {}

void SocketManager::start() {
    receiver.start();
    sender.start();
}

void SocketManager::assign_handler(BlockingThEventHandler* recv_handler) {
    receiver.assign_handler(recv_handler);
}

void SocketManager::send(const Event& ev) {
    sender.push_event(ev);
}

int SocketManager::get_id() const {
    return id;
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
