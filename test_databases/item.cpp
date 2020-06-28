#include "item.h"

const char* MaxStackExceedException::what() const throw() {
    return "Exceeded max amount of stackable!";
}

const char* NegativeStackException::what() const throw() {
    return "Negative amount of stackable!";
}

Item::Item() {}

Item::Item(item_info_t item_info, uint32_t count) : item_info(item_info),
													count(count) {}

nlohmann::json Item::get_info() {
	nlohmann::json info = item_info;
	info["count"] = count;
	return std::move(info);
}

//TODO: Falta manejar el caso del oro, dado que asi como esta solo puedo tener 9999
void Item::set_count(uint32_t count) {
	if (count > STACKABLE_MAX) throw MaxStackExceedException();
	if (count < 0) throw NegativeStackException();
	this->count = count;
}

uint32_t Item::get_count() {
	return count;
}

//TODO: Falta manejar el caso del oro, dado que asi como esta solo puedo tener 9999
void Item::increase_count(uint32_t count) {
	if (this->count + count > STACKABLE_MAX) throw MaxStackExceedException();
	this->count += count;
}

void Item::decrease_count(uint32_t count) {
	if (this->count - count < 0) this->count = 0; // O lanza excepcion?
	this->count -=count;
}													 