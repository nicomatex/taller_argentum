#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

class ConfigurationManager {
   private:
    static float nothing_drop_ev_prob;
    static float gold_drop_ev_prob;
    static float potion_drop_ev_prob;
    static float rand_obj_drop_ev_prob;
    static unsigned int newbie_lvl;
    static unsigned int max_level_difference;
    static float gold_max_secure_mult;
    static float gold_max_secure_expo;
    static float gold_excess_mult;
    static float exp_limit_mult;
    static float exp_limit_expo;
    static unsigned int exp_reduc_percentage;
    static unsigned int critic_prob;
    static float critic_mult;
    static float player_attack_speed;
    static double dodge_threshold;

   public:
    ConfigurationManager();
    ~ConfigurationManager();
    static void init(const char *config_file);
    /*
        Drops probabilities (events)
    */
    static float get_nothing_drop_ev_prob();
    static float get_gold_drop_ev_prob();
    static float get_potion_drop_ev_prob();
    static float get_rand_obj_drop_ev_prob();
    /*
        Player, Experience, Combat
    */
    static unsigned int get_newbie_lvl();
    static unsigned int get_max_level_diff();
    static float get_gold_max_sec_mult();
    static float get_gold_max_sec_expo();
    static float get_gold_exc_mult();
    static float get_exp_limit_mult();
    static float get_exp_limit_expo();
    static unsigned int get_exp_reduc_percentage();
    static unsigned int get_critic_prob();
    static float get_critic_mult();
    static float get_player_attack_speed();
    static double get_dodge_thold();
};

#endif  // CONFIGURATION_MANAGER_H