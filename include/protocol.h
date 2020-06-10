#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>

#include <functional>
#include <string>
#include <vector>

#include "command.h"
#include "socket.h"

class Protocol {
   private:
    std::reference_wrapper<Socket> socket_ref;

   public:
    explicit Protocol(Socket& socket);

    Protocol(const Protocol& other);
    Protocol& operator=(const Protocol& other);

    const Socket& get_socket();

    // Enviar o recibir un caracter
    Protocol& operator<<(const char c);
    Protocol& operator>>(char& c);

    // Enviar o recibir un string, esto es, enviar un uint32 con el tamanio,
    // seguido de su contenido
    Protocol& operator<<(const std::string& str);
    Protocol& operator>>(std::string& str);

    // Los datos de tipo int son comunicados en BIG ENDIAN
    Protocol& operator<<(const uint16_t num);
    Protocol& operator<<(const uint32_t num);
    Protocol& operator>>(uint16_t& num);
    Protocol& operator>>(uint32_t& num);

    Protocol& operator<<(const Command& ev);
    Protocol& operator>>(Command& ev);

    ~Protocol();
};

#endif  //__PROTOCOL_H__
