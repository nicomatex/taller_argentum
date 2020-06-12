#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>

#include <functional>
#include <string>
#include <vector>

#include "event.h"
#include "socket.h"

class Protocol {
   private:
    std::reference_wrapper<Socket> socket_ref;

   public:
    explicit Protocol(Socket& socket);

    Protocol(const Protocol& other);
    Protocol& operator=(const Protocol& other);

    const Socket& get_socket();

    // Los datos de tipo int son comunicados en BIG ENDIAN
    Protocol& operator<<(const uint32_t num);
    Protocol& operator>>(uint32_t& num);

    Protocol& operator<<(const Event& ev);
    Protocol& operator>>(Event& ev);

    ~Protocol();
};

#endif  //__PROTOCOL_H__
