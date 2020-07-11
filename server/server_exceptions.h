#ifndef SERVER_EXCEPTIONS_H
#define SERVER_EXCEPTIONS_H

#include <cstring>
#include <stdexcept>
#include <string>

class ClientDisconnectedException : public std::exception {
   private:
    char err_msg[100];

   public:
    ClientDisconnectedException(ClientId client_id) {
        std::string str =
            "The client: " + std::to_string(client_id) + " has disconnected.";
        std::strncpy(err_msg, str.c_str(), 100);
        err_msg[99] = '\0';
    }
    ClientDisconnectedException(std::string name) {
        std::string str = "The client: " + name + " has disconnected.";
        std::strncpy(err_msg, str.c_str(), 100);
        err_msg[99] = '\0';
    }
    ~ClientDisconnectedException() {}

    const char* what() const noexcept override {
        return err_msg;
    }
};

class DuplicatedPlayerException : public std::exception {
   private:
    char err_msg[100];

   public:
    DuplicatedPlayerException(std::string name) {
        std::string str = "The player: " + name + " is already connected!";
        std::strncpy(err_msg, str.c_str(), 100);
        err_msg[99] = '\0';
    }
    ~DuplicatedPlayerException() {}

    const char* what() const noexcept override {
        return err_msg;
    }
};

#endif  // SERVER_EXCEPTIONS_H
