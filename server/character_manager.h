#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

#include <mutex>
#include <iostream>
#include <fstream>
#include <map>
#include "position.h"

#define MAX_CHAR_NAME 15

typedef struct character {
    char name[MAX_CHAR_NAME + 1];
    int map_id;
    position_t position;
    int head_id;
    int body_id;
} character_t;

typedef uint32_t CharId;

class CharacterAlreadyExistsException : public std::exception {
public:
    const char *what() const throw();
};

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

    /*
        Devuelve un character por movimiento.
        Lanza std::exception() en caso de que name exceda MAX_LENGTH
    */
    character_t create_character(std::string name, int map_id,
                                 position_t pos_player, int head_id,
                                 int body_id);
    /*
        Devuelve true si existe el character, false si no.
    */
    bool character_exists(std::string name);

    /*
        Agrega un personaje al archivo de structs y al diccionario,
        si ya existe, lanza CharacterAlreadyExistsException()
    */
   	void add_character(const character_t &character);

    /*
        Le setea al character con nombre "name", un character.
        Si no existe, lanza CharacterNotFoundException.
        Si el character pasado difiere en nombre, lanza std::exception()
        Se utiliza para persistir el estado actual de la entidad player,
        al archivo de structs.
    */
    void set_character(std::string name, const character_t &character);
    
    /*
        Devuelve el CharId asociado al player_name.
        Si no existe, lanza CharacterNotFoundException.
    */
    CharId get_char_id(std::string name);

    /*
        Devuelve el character asociado al name por movimiento.
        Si no existe, lanza CharacterNotFoundException.
    */
    character_t get_character(std::string name);

    /*
        Hace el dump del diccionario actual al archivo de diccionarios, junto
        con el char_count.
    */
    void save();

    /*
        Imprime la informacion de un personaje.
        Si no existe, lanza CharacterNotFoundException.
    */
    void print_character(std::string name);
    
    /*
        Debe realizarse un save. 
    */
   	~CharacterManager();
};

#endif // CHARACTER_MANAGER_H