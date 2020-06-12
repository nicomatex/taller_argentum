#include "str_translator.h"

std::vector<char> Translator::serialize(const std::string& str) {
    return std::vector<char>(str.begin(), str.end());
}
std::string Translator::deserialize(std::vector<char> v) {
    return std::string(v.begin(), v.end());
}
