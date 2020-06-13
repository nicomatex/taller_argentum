#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <utility>
#include <vector>

#include "../nlohmann/json.hpp"
#include "event.h"

class Translator {
   public:
    static std::vector<uint8_t> serialize(const Event& ev);

    static nlohmann::json deserialize(std::vector<uint8_t> v);
};

#endif  // TRANSLATOR_H
