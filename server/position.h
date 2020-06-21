#ifndef POSITION_H
#define POSITION_H

#include <boost/functional/hash.hpp>

#include "../nlohmann/json.hpp"

typedef struct position {
    unsigned int x;
    unsigned int y;
} position_t;

inline void to_json(nlohmann::json& j, const position_t& p) {
    j["pos"]["x"] = p.x;
    j["pos"]["y"] = p.y;
}

inline void from_json(const nlohmann::json& j, position_t& p) {
    j["pos"]["x"].get_to(p.x);
    j["pos"]["y"].get_to(p.y);
}

class PositionHasher {
   public:
    std::size_t operator()(const position_t& position) const noexcept {
        boost::hash<int> hasher;
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
