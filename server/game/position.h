#ifndef POSITION_H
#define POSITION_H

#include <functional>

#include "../../include/nlohmann/json.hpp"

typedef struct position {
    int x;
    int y;
} position_t;

inline void to_json(nlohmann::json& j, const position_t& p) {
    j["x"] = p.x;
    j["y"] = p.y;
}

inline void from_json(const nlohmann::json& j, position_t& p) {
    j["x"].get_to(p.x);
    j["y"].get_to(p.y);
}

class PositionHasher {
   public:
    std::size_t operator()(const position_t& position) const noexcept {
        std::hash<int> hasher;
        return hasher(position.x) ^ hasher(position.y);
    }
};

class PositionComparator {
   public:
    bool operator()(const position_t& position1,
                    const position_t& position2) const noexcept {
        return position1.x == position2.x && position1.y == position2.y;
    }
};

#endif  // POSITION_H
