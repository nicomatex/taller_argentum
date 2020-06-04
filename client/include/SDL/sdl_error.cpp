#include <cstdarg>
#include <cstdio>

#include "sdl_error.h"

SDLError::SDLError(const char* fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_error, BUF_LEN, fmt, args);
}

const char* SDLError::what() const noexcept { return msg_error; }
