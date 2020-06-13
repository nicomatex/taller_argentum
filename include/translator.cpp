#include "translator.h"

std::vector<uint8_t> Translator::serialize(const Event& ev) {
    return nlohmann::json::to_msgpack(ev.get_json());
}
nlohmann::json Translator::deserialize(std::vector<uint8_t> v) {
    return nlohmann::json::from_msgpack(v);
}
