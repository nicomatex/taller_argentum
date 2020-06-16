#ifndef __MAP_H
#define __MAP_H
#include <boost/functional/hash.hpp>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include "player.h"
#include "../nlohmann/json.hpp"
#include "entity.h"

#define MAP_SIZE 50

typedef struct position {
    unsigned int x;
    unsigned int y;
} position_t;

typedef struct steps {
    int x;
    int y;
} steps_t;

typedef std::unordered_map<unsigned int, position_t> PositionMap;

typedef std::unordered_map<unsigned int, Entity*> EntityMap;

typedef std::unordered_map<unsigned int, unsigned int> ClientMap;

class PositionHasher {
   public:
    std::size_t operator()(const position_t& position) const noexcept {
        boost::hash<int> hasher;
        return hasher(position.x) ^ hasher(position.y);
    }
};

class PositionComparator {
   public:
    bool operator()(const position_t& position1,
                    const position_t& position2) const noexcept {
        return position1.x == position2.x && position1.y == position2.y;
    }
};

void to_json(nlohmann::json& j, const position_t& p) { j["pos"] = {p.x, p.y}; }

void from_json(const nlohmann::json& j, position_t& p) {
    j.at("pos")[0].get_to(p.x);
    j.at("pos")[1].get_to(p.y);
}

class Map {
   private:
    std::mutex m;
    PositionMap position_map;  // clave: id de entidad, valor: position_t
    std::unordered_set<int>
        entity_matrix[MAP_SIZE][MAP_SIZE];  // Set de ids de lo que hay
    // en cada posicion.
    std::unordered_set<position_t, PositionHasher, PositionComparator>
        collision_map;  // Clave: position_t. Contiene los bloques
                        // colisionables.
    position_t get_nearest_free_position(
        position_t position);  // Devuelve la posicion no-
    // colisionable mas cercana.
    nlohmann::json visual_map_info;  // Para mandarsela a los clientes.
    EntityMap entity_map;  // Clave: id de entidad, valor: puntero a la entidad
    ClientMap
        client_map;  // Clave: id de cliente, valor: id de entidad del jugador.

    /* Indica si la posicion indicada tiene un elemento colisionable (no se
     * puede pisar). */
    bool collides(position_t position);

    int
    get_next_id();  // Devuelve el siguiente id a asignar a una nueva entidad.

    /* Agrega una nueva entidad asociada al entity_id en la posicion indicada.*/
    void add_entity(Entity* entity, position_t position);
    
   public:
    Map(nlohmann::json map_info);
    ~Map();
    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(unsigned int entity_id, steps_t steps);


    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    int add_player(nlohmann::json player_info, int client_id);

    /* Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.*/
    void update(unsigned int delta_t);

    Player& get_player(int client_id);

    nlohmann::json get_position_data();
    nlohmann::json get_entity_data();
    nlohmann::json get_map_data();

    /* Devuelve una copia del mapa de posiciones.*/
    PositionMap get_position_map();
};

#endif