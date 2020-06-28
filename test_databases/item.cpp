#include "item.h"
#include <iostream> //Temp

const char* MaxStackExceedException::what() const throw() {
    return "Exceeded max amount of stackable!";
}

const char* NegativeStackException::what() const throw() {
    return "Negative amount of stackable!";
}

Item::Item() {}

Item::Item(item_info_t item_info, uint32_t stack) : item_info(item_info),
													actual_stack(stack) {}

nlohmann::json Item::get_info() {
	nlohmann::json info = item_info;
	info["actual_stack"] = actual_stack;
	return std::move(info);
}

void Item::set_stack(uint32_t stack) {
	if (stack > item_info.max_stack) throw MaxStackExceedException();
	if (stack < 0) throw NegativeStackException();
	this->actual_stack = stack;
}

uint32_t Item::get_stack() {
	return actual_stack;
}

int Item::stack_difference(uint32_t other_stack) {
	if (other_stack < 0) throw NegativeStackException();
	if (other_stack > item_info.max_stack) throw MaxStackExceedException();
	return actual_stack - other_stack;
}

void Item::increase_stack(uint32_t stack) {
	if (this->actual_stack + stack > item_info.max_stack) throw MaxStackExceedException();
	this->actual_stack += stack;
}

void Item::decrease_stack(uint32_t stack) {
	if (this->actual_stack - stack < 0) this->actual_stack = 0; // O lanza excepcion?
	this->actual_stack -=stack;
}													 