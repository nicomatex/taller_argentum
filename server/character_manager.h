#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <fstream>
#include <iostream>
#include <map>
#include <mutex>

#include "../include/types.h"
#include "attribute_manager.h"
#include "game/items/item_container.h"
#include "game/position.h"

#define MAX_CHAR_NAME 15

typedef struct character {
    char name[MAX_CHAR_NAME + 1];
    int map_id;
    position_t position;
    uint32_t head_id;
    uint32_t body_id;
    ItemId helmet_id;
    ItemId armor_id;
    ItemId shield_id;
    ItemId weapon_id;
    unsigned int current_hp;
    unsigned int current_mp;
    inventory_t inventory;
    class_type_t class_type;
    race_type_t race_type;
    unsigned int current_level;
    unsigned int current_exp;
    bool alive;
} character_t;

typedef uint32_t CharId;

class CharacterNotFoundException : public std::exception {
   public:
    const char *what() const throw();
};

class CharacterManager {
   private:
    std::mutex m;
    int char_count;
    std::fstream f_char_stream;
    std::fstream f_map_stream;
    std::map<std::string, CharId> char_map;

   public:
    CharacterManager(const char *f_char, const char *f_map);
    /**
     * @brief Devuelve true si existe el character, false si no.
     * 
     * @param name 
     * @return true 
     * @return false 
     */
    bool character_exists(std::string name);

   /**
    * @brief Agrega un personaje al archivo de structs y al diccionario,
    *        si ya existe, lanza CharacterAlreadyExistsException()
    * 
    * @param character_info 
    */
    void add_character(const nlohmann::json &character_info);
    /**
     * @brief Se utiliza para persistir el estado actual de la entidad character,
     *        al archivo de structs.
     *        Si no existe el character, lanza excepcion.
     * 
     * @param character_info 
     */
    void set_character(const nlohmann::json &character_info);

    /**
     * @brief Devuelve el CharId asociado al player_name.
     *        Si no existe, lanza CharacterNotFoundException.
     * 
     * @param name 
     * @return CharId 
     */
    CharId get_char_id(std::string name);

    /**
     * @brief  Devuelve el character asociado al name por movimiento.
     *         Si no existe, lanza CharacterNotFoundException.
     * 
     * @param name 
     * @return nlohmann::json 
     */
    nlohmann::json get_character(std::string name);

    /**
     * @brief  Hace el dump del diccionario actual al archivo de diccionarios, junto
     *         con el char_count.
     * 
     */
    void save();

   /**
    * @brief Imprime la informacion de un personaje.
    *        Si no existe, lanza CharacterNotFoundException.
    * 
    * @param name 
    */
    void print_character(std::string name);

    /**
     * @brief Debe realizarse un save.
     * 
     */
    ~CharacterManager();
};

#endif  // CHARACTER_MANAGER_H