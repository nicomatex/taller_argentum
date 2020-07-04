#include "experience_component.h"
#include <cmath>
#include <iostream>

ExperienceComponent::ExperienceComponent(unsigned int level, unsigned int exp) :
										 current_level(level), current_exp(exp) {}

ExperienceComponent::~ExperienceComponent() {}

void ExperienceComponent::add_exp(int exp) {
	while (exp > 0) {
		unsigned int exp_next_level = exp_to_next_level(current_level,
												        current_exp);
		int difference = exp - exp_next_level;
		if (difference >= 0) {
			current_exp += exp_next_level;
			current_level++;
			exp -= exp_next_level;
		} else {
			current_exp += exp;
			exp = 0;
		}
	}
}

void ExperienceComponent::reduce() {
	unsigned int base_exp = get_xp_limit_level(current_level - 1);
	int exp_lost = float(current_exp - base_exp)* (EXP_REDU/(float)100);
	current_exp -= exp_lost;
}

unsigned int ExperienceComponent::get_level() {
	return current_level;
}

void ExperienceComponent::set_level(unsigned int level) {
	current_level = level;
	current_exp = get_xp_limit_level(current_level - 1);
}

int ExperienceComponent::exp_to_next_level(unsigned int current_level,
										   unsigned int current_exp) {
	int current_limit = get_xp_limit_level(current_level);
	int difference = current_limit - current_exp;
	return (difference > 0) ? difference : 0;
}

int ExperienceComponent::get_xp_limit_level(unsigned int level) const {
	return (int)(EXP_MULT * std::pow((double)level, EXP_EXPO));
}

nlohmann::json ExperienceComponent::get_persist_data() const {
	nlohmann::json json_exp;
	json_exp["curr_level"] = current_level;
	json_exp["curr_exp"] = current_exp;
	return std::move(json_exp);
}

nlohmann::json ExperienceComponent::get_data() const {
	nlohmann::json json_exp;
	unsigned int base_exp = get_xp_limit_level(current_level - 1);
	json_exp["curr_level"] = current_level;
	json_exp["curr_exp"] = current_exp - base_exp;
	json_exp["limit_exp"] = get_xp_limit_level(current_level) - base_exp;
	return std::move(json_exp);
}
