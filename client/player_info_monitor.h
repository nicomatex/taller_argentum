#ifndef __PLAYER_INFO_MONITOR_H
#define __PLAYER_INFO_MONITOR_H

#include <mutex>
#include <string>
#include "../include/nlohmann/json.hpp"


class PlayerInfoMonitor {
   private:
    std::string spell_name;
    std::mutex m;

    int attack_pts;
    int defense_pts;

   public:
    PlayerInfoMonitor();
    ~PlayerInfoMonitor();

    std::string get_spell_name();
    int get_attack_pts();
    int get_defense_pts();

    void update(nlohmann::json update);
};

#endif