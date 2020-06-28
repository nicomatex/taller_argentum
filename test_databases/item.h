#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "types.h"
#include "json.h"

#define STACKABLE_MAX 9999

class MaxStackExceedException : public std::exception {
   public:
    const char *what() const throw();
};

class NegativeStackException : public std::exception {
   public:
    const char *what() const throw();
};

typedef enum {weapon, armor, potion, gold} item_type_t;

typedef struct item_info {
	std::string name;
	ItemId id;
	item_type_t type;
	int sprite_id;
} item_info_t;

inline void to_json(nlohmann::json &j, const item_info_t &i) {
	j["name"] = i.name;
	j["id"] = i.id;
    j["type"] = i.type;
    j["sprite_id"] = i.sprite_id;
}

inline void from_json(const nlohmann::json &j, item_info_t &i) {
	j["name"].get_to(i.name);
	j["id"].get_to(i.id);
    j["type"].get_to(i.type);
	j["sprite_id"].get_to(i.sprite_id);
}

class Item {
   private:
   	item_info_t item_info;
   	uint32_t count;
    //uin32_t max_count; <-- el maximo stackable
   public:
    Item();
   	Item(item_info_t item_info, uint32_t count = 0);
   	virtual ~Item() {};
   	virtual nlohmann::json get_info();
    void set_count(uint32_t count);
    uint32_t get_count();
    void increase_count(uint32_t count);
    void decrease_count(uint32_t count);
};

#endif // ITEM_H
