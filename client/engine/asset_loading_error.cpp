#include "asset_loading_error.h"

#include <cstdarg>
#include <cstdio>

AssetLoadingError::AssetLoadingError(const char* fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg_error, BUF_LEN, fmt, args);
}

const char* AssetLoadingError::what() const noexcept {
    return msg_error;
}
