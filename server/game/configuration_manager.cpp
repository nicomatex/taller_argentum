#include "configuration_manager.h"

#include <fstream>
#include <iostream>

#include "../../include/my_exception.h"
#include "../../include/nlohmann/json.hpp"

float ConfigurationManager::nothing_drop_ev_prob = 100;
float ConfigurationManager::gold_drop_ev_prob = 0;
float ConfigurationManager::potion_drop_ev_prob = 0;
float ConfigurationManager::rand_obj_drop_ev_prob = 0;
unsigned int ConfigurationManager::newbie_lvl = 1;
unsigned int ConfigurationManager::max_level_difference = UINT32_MAX;
float ConfigurationManager::gold_max_secure_mult = 1;
float ConfigurationManager::gold_max_secure_expo = 1;
float ConfigurationManager::gold_excess_mult = 1;
float ConfigurationManager::exp_limit_mult = 1;
float ConfigurationManager::exp_limit_expo = 1;
unsigned int ConfigurationManager::exp_reduc_percentage = 5;
unsigned int ConfigurationManager::critic_prob = 0;
float ConfigurationManager::critic_mult = 1;
float ConfigurationManager::player_attack_speed = 1;
double ConfigurationManager::dodge_threshold = 0;
unsigned int ConfigurationManager::spawn_interval = 7000;

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

    if (config.count("NOTHING_PROB"))
        nothing_drop_ev_prob = config["NOTHING_PROB"];
    if (config.count("GOLD_PROB"))
        gold_drop_ev_prob = config["GOLD_PROB"];
    if (config.count("POTION_PROB"))
        potion_drop_ev_prob = config["POTION_PROB"];
    if (config.count("RAND_OBJECT_PROB"))
        rand_obj_drop_ev_prob = config["RAND_OBJECT_PROB"];
    if (config.count("NEWBIE_LVL"))
        newbie_lvl = config["NEWBIE_LVL"];
    if (config.count("MAX_LVL_DIFFERENCE"))
        max_level_difference = config["MAX_LVL_DIFFERENCE"];
    if (config.count("GOLD_MAX_SECURE_MULT"))
        gold_max_secure_mult = config["GOLD_MAX_SECURE_MULT"];
    if (config.count("GOLD_MAX_SECURE_EXPO"))
        gold_max_secure_expo = config["GOLD_MAX_SECURE_EXPO"];
    if (config.count("GOLD_EXCESS_MULT"))
        gold_excess_mult = config["GOLD_EXCESS_MULT"];
    if (config.count("EXP_LIMIT_MULT"))
        exp_limit_mult = config["EXP_LIMIT_MULT"];
    if (config.count("EXP_LIMIT_EXPO"))
        exp_limit_expo = config["EXP_LIMIT_EXPO"];
    if (config.count("EXP_REDUC_PERCENTAGE"))
        exp_reduc_percentage = config["EXP_REDUC_PERCENTAGE"];
    if (config.count("CRITIC_PROB"))
        critic_prob = config["CRITIC_PROB"];
    if (config.count("CRITIC_MULT"))
        critic_mult = config["CRITIC_MULT"];
    if (config.count("PLAYER_ATTACK_SPEED"))
        player_attack_speed = config["PLAYER_ATTACK_SPEED"];
    if (config.count("DODGE_THRESHOLD"))
        dodge_threshold = config["DODGE_THRESHOLD"];
    if (config.count("SPAWN_INTERVAL"))
        spawn_interval = config["SPAWN_INTERVAL"];
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

float ConfigurationManager::get_player_attack_speed() {
    return player_attack_speed;
}

double ConfigurationManager::get_dodge_thold() {
    return dodge_threshold;
}

unsigned int ConfigurationManager::get_spawn_interval() {
    return spawn_interval;
}
