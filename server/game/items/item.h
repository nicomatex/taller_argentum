#ifndef ITEM_H
#define ITEM_H

#include <stdint.h>

#include <string>

#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"

class MaxStackExceedException : public std::exception {
   public:
    const char *what() const throw();
};

class NegativeStackException : public std::exception {
   public:
    const char *what() const throw();
};

typedef struct item_info {
    std::string name;
    ItemId id;
    item_type_t type;
    uint32_t sprite_id;
    unsigned int gold_value;
} item_info_t;

inline void to_json(nlohmann::json &j, const item_info_t &i) {
    j["name"] = i.name;
    j["id"] = i.id;
    j["type"] = i.type;
    j["sprite_id"] = i.sprite_id;
    j["gold_value"] = i.gold_value;
}

inline void from_json(const nlohmann::json &j, item_info_t &i) {
    j["name"].get_to(i.name);
    j["id"].get_to(i.id);
    j["type"].get_to(i.type);
    j["sprite_id"].get_to(i.sprite_id);
    j["gold_value"].get_to(i.gold_value);
}

class Item {
   private:
    item_info_t item_info;
    uint32_t actual_stack;

   public:
    Item();
    Item(item_info_t item_info, uint32_t stack = 0);
    virtual ~Item(){};
    virtual nlohmann::json get_data() const;
    virtual nlohmann::json get_persist_data() const;
    void set_stack(uint32_t stack);
    uint32_t get_stack() const;
    ItemId get_id() const;
    uint32_t get_sprite_id() const;
    item_type_t get_type() const;
    long int stack_difference(uint32_t other_stack);
    void increase_stack(uint32_t stack);
    void decrease_stack(uint32_t stack);
    uint32_t get_gold_value() const;
};

#endif  // ITEM_H
