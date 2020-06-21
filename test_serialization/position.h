#ifndef POSITION_H
#define POSITION_H

#include <boost/functional/hash.hpp>

#include "json.h"

typedef struct position {
    unsigned int x;
    unsigned int y;
} position_t;

inline void to_json(nlohmann::json& j, const position_t& p) {
    j["pos"] = {p.x, p.y};
}

inline void from_json(const nlohmann::json& j, position_t& p) {
    j.at("pos")[0].get_to(p.x);
    j.at("pos")[1].get_to(p.y);
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
