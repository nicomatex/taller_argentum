#ifndef __SOCKET_EXCEPTION_H__
#define __SOCKET_EXCEPTION_H__

#include <stdexcept>
#include <string>

class ConnectionClosedSocketException : public std::exception {
   private:
    std::string error;

   public:
    ConnectionClosedSocketException();

    virtual const char* what() const noexcept override;

    ~ConnectionClosedSocketException();
};

#endif  //__SOCKET_EXCEPTION_H__
