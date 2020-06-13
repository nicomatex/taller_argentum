#include <cstdarg>
#include <cstdio>

#include "engine_error.h"

EngineError::EngineError(const char* fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_error, BUF_LEN, fmt, args);
}

const char* EngineError::what() const noexcept { return msg_error; }
