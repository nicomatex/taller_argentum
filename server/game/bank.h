#ifndef BANK_H
#define BANK_H

#include "items/item_container.h"
#include "../../include/nlohmann/json.hpp"
#include <unordered_map>

#include "entities/player.h"


typedef ItemContainer Vault;

class Bank {
   private:
    static std::unordered_map<std::string, Vault> bank_accounts;
    static Vault& get_vault(std::string player_name);
   public:
    Bank();
    ~Bank();
    static nlohmann::json get_vault_persist_data(std::string player_name);
    static nlohmann::json get_vault_data(std::string player_name);
    static void add_account(std::string player_name, nlohmann::json vault_info);
    static nlohmann::json remove_account(std::string player_name);
    static bool account_exists(std::string player_name);

    static void deposit_gold(uint32_t amount, Player *player);
    static void withdraw_gold(uint32_t amount, Player *player);
    static void deposit_item(SlotId slot, uint32_t amount, Player *player);
    static void withdraw_item(SlotId slot, uint32_t amount, Player *player);
};

#endif // BANK_H