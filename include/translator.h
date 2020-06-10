#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <string>
#include <utility>
#include <vector>

class Traductor {
   public:
    static std::vector<char> serializar(const std::string& str);

    static std::string deserializar(std::vector<char> v);
};

#endif  // TRANSLATOR_H
