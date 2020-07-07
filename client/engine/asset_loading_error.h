#ifndef __ERROR_H
#define __ERROR_H

/* ------ Includes ---------*/
#include <string>
#include <typeinfo>

#define BUF_LEN 256

/* ------ Interfaz ---------*/
class AssetLoadingError : public std::exception {
   private:
    char msg_error[BUF_LEN];

   public:
    explicit AssetLoadingError(const char* fmt, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~AssetLoadingError() noexcept {}
};

#endif
