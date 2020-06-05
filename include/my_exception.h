#ifndef __MY_EXCEPTION_H__
#define __MY_EXCEPTION_H__

#include <stdexcept>

#define BUFF_SIZE 256

class MyException : public std::exception {
   private:
    char error_msg[BUFF_SIZE];

   public:
    MyException() noexcept;

    MyException(const char* format, ...) noexcept;

    virtual const char* what() const noexcept;

    ~MyException();
};

#endif  //__MY_EXCEPTION_H__
