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

nlohmann::json Item::get_data() {
    nlohmann::json info = item_info;
    info["actual_stack"] = actual_stack;
    return info;
}

void Item::set_stack(uint32_t stack) {
    if (stack > UINT32_MAX)
        throw MaxStackExceedException();
    actual_stack = stack;
}

uint32_t Item::get_stack() {
    return actual_stack;
}

ItemId Item::get_id() {
    return item_info.id;
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