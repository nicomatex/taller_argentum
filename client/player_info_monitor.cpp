#include "player_info_monitor.h"

PlayerInfoMonitor::PlayerInfoMonitor()
    : spell_name("Explosion"), attack_pts(15), defense_pts(20) {}
PlayerInfoMonitor::~PlayerInfoMonitor() {}

std::string PlayerInfoMonitor::get_spell_name() {
    std::unique_lock<std::mutex> l(m);
    return spell_name;
}

int PlayerInfoMonitor::get_attack_pts(){
    std::unique_lock<std::mutex> l(m);
    return attack_pts;
}

int PlayerInfoMonitor::get_defense_pts(){
    std::unique_lock<std::mutex> l(m);
    return defense_pts;
}

void PlayerInfoMonitor::update(nlohmann::json update) {
    std::unique_lock<std::mutex> l(m);
    //TODO
}