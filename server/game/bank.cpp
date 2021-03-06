#include "bank.h"

#include <iostream>

#include "../../include/my_exception.h"

Bank::Bank() {}

Bank::~Bank() {}

Bank& Bank::get_instance(){
    static Bank bank;
    return bank;
}

bool Bank::account_exists(std::string player_name) {
    return (!bank_accounts.count(player_name)) ? false : true;
}

Vault &Bank::get_vault(std::string player_name) {
    if (!account_exists(player_name))
        throw MyException("Bank: No bank account with name : %s exists",
                          player_name);
    return bank_accounts.at(player_name);
}

nlohmann::json Bank::get_vault_persist_data(std::string player_name) {
    return get_vault(player_name).get_persist_data();
}

nlohmann::json Bank::get_vault_data(std::string player_name) {
    return get_vault(player_name).get_data();
}

void Bank::add_account(std::string player_name, nlohmann::json vault_info) {
    if (account_exists(player_name))
        throw MyException("Bank: Bank account with name : %s, already exists",
                          player_name);
    Vault vault(vault_info);
    bank_accounts[player_name] = std::move(vault);
}

nlohmann::json Bank::remove_account(std::string player_name) {
    nlohmann::json json_vault = get_vault_persist_data(player_name);
    bank_accounts.erase(player_name);
    return json_vault;
}

void Bank::deposit_gold(uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Gold *gold = player->remove_gold(amount);
    vault.add_gold(gold);
    delete gold;
}

void Bank::withdraw_gold(uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Gold *gold = vault.remove_gold(amount);
    try { 
        player->add_item(gold);
    } catch (const FullItemContainerException& e) {
        player->get_map().push_log(MapLogFactory::inventory_full(player->get_name()));
        vault.add_gold(gold);
        delete gold;
    }
}

void Bank::deposit_item(SlotId slot, uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Item *item = player->remove_item(slot, amount);
    if (!item)
        return;
    try {
        vault.add(item);
    } catch (const FullItemContainerException& e) {
        player->add_item(item);
    }
}

void Bank::withdraw_item(SlotId slot, uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Item *item = vault.remove(slot, amount);
    try { 
        player->add_item(item);   
    } catch (const FullItemContainerException& e) {
        player->get_map().push_log(MapLogFactory::inventory_full(player->get_name()));
        vault.add(item);
    }
}
