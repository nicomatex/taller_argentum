#ifndef __TRADUCTOR_H__
#define __TRADUCTOR_H__

#include <string>
#include <utility>
#include <vector>

class Traductor {
   public:
    static std::vector<char> serializar(const std::string& str);

    static std::string deserializar(std::vector<char> v);
};

#endif  //__TRADUCTOR_H__
