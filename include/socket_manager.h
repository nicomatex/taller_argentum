#ifndef SOCKET_HANDLER_H
#define SOCKET_HANDLER_H

#include <utility>

#include "blocking_th_event_handler.h"
#include "socket.h"
#include "th_socket_receiver.h"
#include "th_socket_sender.h"

class SocketManager {
   private:
    const int client_id;
    Socket socket;
    ThSocketReceiver receiver;
    ThSocketSender sender;

   public:
    SocketManager(int id, Socket socket,
                  BlockingThEventHandler& ReceiveHandler);
    SocketManager(Socket& socket, BlockingThEventHandler& ReceiveHandler);

    void start();

    void send(const Event& ev);

    int get_id() const;

    bool is_done() const;

    void stop(bool shutdown);

    void join();

    ~SocketManager();
};

#endif  // SOCKET_HANDLER_H
