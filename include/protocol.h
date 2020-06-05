#ifndef __PROTOCOLO_H__
#define __PROTOCOLO_H__

#include <stdint.h>

#include <string>
#include <vector>

#include "socket.h"

class Protocol {
   private:
    Socket& socket;

   public:
    explicit Protocol(Socket& socket);

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

    ~Protocol();
};

#endif  //__PROTOCOLO_H__
