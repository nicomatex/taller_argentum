#include "configuration_manager.h"

#include <fstream>
#include <iostream>

#include "../include/nlohmann/json.hpp"
#include "../include/my_exception.h"


float ConfigurationManager::nothing_drop_ev_prob;
float ConfigurationManager::gold_drop_ev_prob;
float ConfigurationManager::potion_drop_ev_prob;
float ConfigurationManager::rand_obj_drop_ev_prob;
unsigned int ConfigurationManager::newbie_lvl;
unsigned int ConfigurationManager::max_level_difference;
float ConfigurationManager::gold_max_secure_mult;
float ConfigurationManager::gold_max_secure_expo;
float ConfigurationManager::gold_excess_mult;
float ConfigurationManager::exp_limit_mult;
float ConfigurationManager::exp_limit_expo;
unsigned int ConfigurationManager::exp_reduc_percentage;
unsigned int ConfigurationManager::critic_prob;
float ConfigurationManager::critic_mult;
double ConfigurationManager::dodge_threshold;

ConfigurationManager::ConfigurationManager() {}

ConfigurationManager::~ConfigurationManager() {}

void ConfigurationManager::init(const char *config_file) {
    std::ifstream config_istream(config_file);
    if (!config_istream.is_open())
        throw MyException(
            "ConfigurationManager: Error opening config file of constants: %s",
            config_file);
    nlohmann::json config;
    config_istream >> config;
    
    nothing_drop_ev_prob = config["NOTHING_PROB"];
    gold_drop_ev_prob = config["GOLD_PROB"];
    potion_drop_ev_prob = config["POTION_PROB"];
    rand_obj_drop_ev_prob = config["RAND_OBJECT_PROB"];
    newbie_lvl = config["NEWBIE_LVL"];
    max_level_difference = config["MAX_LVL_DIFFERENCE"];
    gold_max_secure_mult = config["GOLD_MAX_SECURE_MULT"];
    gold_max_secure_expo = config["GOLD_MAX_SECURE_EXPO"];
    gold_excess_mult = config["GOLD_EXCESS_MULT"];
    exp_limit_mult = config["EXP_LIMIT_MULT"];
    exp_limit_expo = config["EXP_LIMIT_EXPO"];
    exp_reduc_percentage = config["EXP_REDUC_PERCENTAGE"];
    critic_prob = config["CRITIC_PROB"];
    critic_mult = config["CRITIC_MULT"];
    dodge_threshold = config["DODGE_THRESHOLD"];
}

float ConfigurationManager::get_nothing_drop_ev_prob() {
    return nothing_drop_ev_prob;
}

float ConfigurationManager::get_gold_drop_ev_prob() {
    return gold_drop_ev_prob;
}

float ConfigurationManager::get_potion_drop_ev_prob() {
    return potion_drop_ev_prob;
}

float ConfigurationManager::get_rand_obj_drop_ev_prob() {
    return rand_obj_drop_ev_prob;
}

unsigned int ConfigurationManager::get_newbie_lvl() {
    return newbie_lvl;
}

unsigned int ConfigurationManager::get_max_level_diff() {
    return max_level_difference;
}

float ConfigurationManager::get_gold_max_sec_mult() {
    return gold_max_secure_mult;
}

float ConfigurationManager::get_gold_max_sec_expo() {
    return gold_max_secure_expo;
}

float ConfigurationManager::get_gold_exc_mult() {
    return gold_excess_mult;
}

float ConfigurationManager::get_exp_limit_mult() {
    return exp_limit_mult;
}

float ConfigurationManager::get_exp_limit_expo() {
    return exp_limit_expo;
}

unsigned int ConfigurationManager::get_exp_reduc_percentage() {
    return exp_reduc_percentage;
}

unsigned int ConfigurationManager::get_critic_prob() {
    return critic_prob;
}

float ConfigurationManager::get_critic_mult() {
    return critic_mult;
}

double ConfigurationManager::get_dodge_thold() {
    return dodge_threshold;
}
