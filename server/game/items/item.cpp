#include "item.h"

#include <iostream>  //Temp

const char* MaxStackExceedException::what() const throw() {
    return "Exceeded max amount of stackable!";
}

const char* NegativeStackException::what() const throw() {
    return "Negative amount of stackable!";
}

Item::Item() {}

Item::Item(item_info_t item_info, uint32_t stack) : item_info(item_info) {
    if (stack > UINT32_MAX)
        throw MaxStackExceedException();
    actual_stack = stack;
}

nlohmann::json Item::get_data() const {
    nlohmann::json info;
    info["actual_stack"] = actual_stack;
    info["item_id"] = item_info.sprite_id;
    info["name"] = item_info.name;
    info["type"] = item_info.type;
    return info;
}

nlohmann::json Item::get_persist_data() const {
    nlohmann::json info = item_info;
    info["actual_stack"] = actual_stack;
    return info;
}

void Item::set_stack(uint32_t stack) {
    if (stack > UINT32_MAX)
        throw MaxStackExceedException();
    actual_stack = stack;
}

uint32_t Item::get_stack() const {
    return actual_stack;
}

ItemId Item::get_id() const {
    return item_info.id;
}

uint32_t Item::get_sprite_id() const {
    return item_info.sprite_id;
}

item_type_t Item::get_type() const {
    return item_info.type;
}

int Item::stack_difference(uint32_t other_stack) {
    return actual_stack - other_stack;
}

void Item::increase_stack(uint32_t stack) {
    if (actual_stack + stack > UINT32_MAX)
        throw MaxStackExceedException();
    actual_stack += stack;
}

void Item::decrease_stack(uint32_t stack) {
    if (actual_stack < stack) {
        actual_stack = 0;  // O lanza excepcion?
    } else {
        actual_stack -= stack;
    }
}