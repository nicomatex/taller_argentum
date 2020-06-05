#include "translator.h"

std::vector<char> Traductor::serializar(const std::string& str) {
    return std::vector<char>(str.begin(), str.end());
}
std::string Traductor::deserializar(std::vector<char> v) {
    return std::string(v.begin(), v.end());
}
