#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <utility>
#include <vector>

#include "../event.h"
#include "../nlohmann/json.hpp"

class Translator {
   public:
    static std::vector<uint8_t> serialize(const Event& ev);

    static nlohmann::json deserialize(std::vector<uint8_t> v);
};

#endif  // TRANSLATOR_H
