#include <iostream>

#include "../../include/translator.h"
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    json json_msg = {"ev_id", 4, {"player_id", 5, "name", "Hello"}};

    std::vector<uint8_t> v = json::to_msgpack(json_msg);

    return 0;
}
