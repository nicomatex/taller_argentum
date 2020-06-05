#include "my_exception.h"

#include <string.h>

#include <cstdarg>

#define ERROR "Error: "
#define ERRNO_ERR "StdErr: "
#define ERR_SIZE 7
#define STDERR_SIZE 7

MyException::MyException() noexcept {
    MyException("No error message");
}

MyException::MyException(const char* format, ...) noexcept {
    memset(error_msg, 0, BUFF_SIZE);
    int _errno = errno;
    strcpy(error_msg, ERROR);
    int s = ERR_SIZE;

    va_list args;
    va_start(args, format);
    s += vsnprintf(error_msg, BUFF_SIZE, format, args);
    va_end(args);
    error_msg[BUFF_SIZE - 1] = 0;
    if (_errno == 0)
        return;
    error_msg[s++] = ';';
    error_msg[s++] = ' ';
    strcpy(error_msg + s, ERRNO_ERR);
    s += STDERR_SIZE;
    strncpy(error_msg + s, strerror(_errno), BUFF_SIZE - s);
    error_msg[BUFF_SIZE - 1] = 0;
}

const char* MyException::what() const noexcept {
    return error_msg;
}

MyException::~MyException() {}
