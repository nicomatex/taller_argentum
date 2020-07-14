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
    std::cout << "add " << std::endl;
    std::cout << vault_info << std::endl;
    bank_accounts[player_name] = std::move(vault);
    std::cout << "la info es " << get_vault_persist_data(player_name) << std::endl;
}

nlohmann::json Bank::remove_account(std::string player_name) {
    nlohmann::json json_vault = get_vault_persist_data(player_name);
    std::cout << "remove " << std::endl;
    std::cout << json_vault << std::endl;
    bank_accounts.erase(player_name);
    std::cout << "aca me rompi" << std::endl;
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
    player->add_item(gold);
}

void Bank::deposit_item(SlotId slot, uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Item *item = nullptr;
    try {
        item = player->remove_item(slot, amount);
        if (!item)
            return;
        vault.add(item);
    } catch (const FullItemContainerException& e) {
        player->add_item(item);
    }
}

void Bank::withdraw_item(SlotId slot, uint32_t amount, Player *player) {
    Vault &vault = get_vault(player->get_name());
    Item *item = vault.remove(slot, amount);
    player->add_item(item);
}
