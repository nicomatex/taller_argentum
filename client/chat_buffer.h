#ifndef __CHAT_BUFFER_H
#define __CHAT_BUFFER_H

#include <mutex>
#include <queue>
#include <string>

#include "views/game_view/chat.h"

/**
 * @brief Buffer donde se almacenan los mensajes de chat provenientes del
 * servidor.
 *
 */
class ChatBuffer {
   private:
    std::mutex m;
    std::queue<std::string> buffer;

   public:
    ChatBuffer();
    ~ChatBuffer();

    /**
     * @brief Agrega un mensaje al buffer.
     *
     * @param message Mensaje a agregar.
     */
    void push(std::string message);

    /**
     * @brief Flushea todos los mensajes almacenados en el buffer en un chat.
     *
     * @param chat Chat en el cual se deben imprimir los mensajes.
     */
    void flush(Chat &chat);
};

#endif