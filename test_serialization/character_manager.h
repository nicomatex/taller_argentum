#ifndef CHARACTER_MANAGER_H
#define CHARACTER_MANAGER_H

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

class CharacterManager {
   private:
    int char_count;
    std::fstream f_char_stream;
    std::fstream f_map_stream;
    std::map<std::string, CharId> char_map;
   public:
   	CharacterManager(const char *f_char, const char *f_map);

    /*
        Devuelve un character por movimiento.
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
        si ya existe, tira excepcion.
    */
   	void add_character(const character_t &character);

    /*
        Le setea a al character con nombre "name", un character.
        Lanza excepcion si el character pasado difiere en nombre.
        (eso se utiliza para hacer updates, con lo que el character
        ya debe estar agregado, y si se quiere hacer un update, se puede
        llamar a get_character, modificar lo que devuelve, y setearlo)
    */
    void set_character(std::string name, const character_t &character);
    
    /*
        Devuelve el CharId asociado al player_name.
        Lanza excepcion si player_name no existe.
    */
    CharId get_char_id(std::string player_name);

    /*
        Devuelve el character asociado al name por movimiento.
        Si no existe, lanza exception.
    */
    character_t get_character(std::string name);
    /*
        Hace el dump del diccionario actual al archivo de diccionarios, junto
        con el char_count.
        Para hacer saves esporadicos del diccionario.
        TODO: Falta ver aca conectar algo que me de la informacion actual en el juego
        de los characters(que son players en este momento), para yo hacer un get_character(),
        actualizar lo que cambio, y hacer set_character (para todos los personajes que estan jugando).
    */
    void save();
    /*
        Debe realizarse un save. 
    */
   	~CharacterManager();
};

#endif // CHARACTER_MANAGER_H