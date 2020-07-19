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
    /**
     * @brief Devuelve una referencia al vault asociado a un player.
     * Lanza MyException en caso de no existir una cuenta asociada al player.
     * 
     * @param player_name 
     * @return Vault& 
     */
    Vault& get_vault(std::string player_name);
   public:
    ~Bank();
    static Bank& get_instance();
    /**
     * @brief Devuelve un json que representa el vault, para luego convertirlo
     * a inventory_t (de forma automatica) al momento de persistir el personaje.
     * Lanza MyException en caso de no existir una cuenta asociada al player.
     * 
     * @param player_name 
     * @return nlohmann::json 
     */
    nlohmann::json get_vault_persist_data(std::string player_name);
    /**
     * @brief Devuelve un json que representa el contenido actual
     * del vault asociado al player.
     * Lanza MyException en caso de no existir una cuenta asociada al player.
     * 
     * @param player_name 
     * @return nlohmann::json 
     */
    nlohmann::json get_vault_data(std::string player_name);
    /**
     * @brief Agrega una entrada en el diccionario de cuentas asociada a
     * player_name, creando un vault a partir de vault_info
     * Lanza MyException en caso de no existir una cuenta asociada al player.
     * 
     * @param player_name 
     * @param vault_info 
     */
    void add_account(std::string player_name, nlohmann::json vault_info);
    /**
     * @brief Remueve del diccionario a player_name, devolviendo un json
     * que representa la informacion a persistir de la boveda del personaje.
     * Lanza MyException en caso de que ya exista una cuenta asociada al player.
     * 
     * @param player_name 
     * @return nlohmann::json 
     */
    nlohmann::json remove_account(std::string player_name);
    bool account_exists(std::string player_name);
    /**
     * @brief Extrae de la billetera del jugador amount cantidad
     * de oro, y la deposita en su boveda.
     * En caso de superar la cantidad actual que posee en la billetera,
     * se deposita la totalidad de la misma.
     * 
     * @param amount 
     * @param player 
     */
    void deposit_gold(uint32_t amount, Player *player);
    /**
     * @brief Se extrae de la boveda del jugador amount cantidad de oro
     * y se deposita en la billetera del mismo.
     * En caso de que la cantidad actual que posee en la boveda sea menor
     * a amount, se extrae la totalidad de la misma.
     * 
     * @param amount 
     * @param player 
     */
    void withdraw_gold(uint32_t amount, Player *player);
    /**
     * @brief Se deposita en la boveda del jugador amount cantidad del item que se encuentra
     * en el slot del inventario.
     * En caso de que la cantidad amount supere el stack actual del item en el
     * inventario, se deposita en su totalidad.
     * 
     * @param slot 
     * @param amount 
     * @param player 
     */
    void deposit_item(SlotId slot, uint32_t amount, Player *player);
    /**
     * @brief Se retira de la boveda del jugador amount cantidad del item que se encuentra
     * en el slot del vault, y deposita en su inventario.
     * En caso de que la cantidad amount supere el stack actual del item en el
     * vault, se retira en su totalidad.
     * 
     * @param slot 
     * @param amount 
     * @param player 
     */
    void withdraw_item(SlotId slot, uint32_t amount, Player *player);
};

#endif // BANK_H