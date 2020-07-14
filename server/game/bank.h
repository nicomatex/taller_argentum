#ifndef BANK_H
#define BANK_H

#include "items/item_container.h"
#include "../../include/nlohmann/json.hpp"
#include <unordered_map>

#include "entities/player.h"


typedef ItemContainer Vault;

class Bank {
   private:
    Bank();
    std::unordered_map<std::string, Vault> bank_accounts;
    Vault& get_vault(std::string player_name);
   public:
    ~Bank();
    static Bank& get_instance();
    nlohmann::json get_vault_persist_data(std::string player_name);
    nlohmann::json get_vault_data(std::string player_name);
    void add_account(std::string player_name, nlohmann::json vault_info);
    nlohmann::json remove_account(std::string player_name);
    bool account_exists(std::string player_name);

    void deposit_gold(uint32_t amount, Player *player);
    void withdraw_gold(uint32_t amount, Player *player);
    void deposit_item(SlotId slot, uint32_t amount, Player *player);
    void withdraw_item(SlotId slot, uint32_t amount, Player *player);
};

#endif // BANK_H