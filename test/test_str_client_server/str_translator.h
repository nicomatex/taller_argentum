#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <utility>
#include <vector>

class Translator {
   public:
    static std::vector<char> serialize(const std::string& str);

    static std::string deserialize(std::vector<char> v);
};

#endif  // TRANSLATOR_H
