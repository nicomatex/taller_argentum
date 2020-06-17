#ifndef __MAP_H
#define __MAP_H

#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "../nlohmann/json.hpp"
#include "entity.h"
#include "position.h"
#include <cstdint>

#define MAP_SIZE 50

class Player;

typedef struct steps {
    int x;
    int y;
} steps_t;

typedef std::unordered_map<uint32_t, position_t> PositionMap;

typedef std::unordered_map<uint32_t, Entity*> EntityMap;

typedef std::unordered_map<uint32_t, uint32_t> ClientMap;

class Map {
   private:
    std::mutex m;
    // clave: id de entidad, valor: position_t
    PositionMap position_map;
    // Set de ids de lo que hay en cada posicion.
    std::unordered_set<uint32_t> entity_matrix[MAP_SIZE][MAP_SIZE];
    // Clave: position_t. Contiene los bloques colisionables.
    std::unordered_set<position_t, PositionHasher, PositionComparator>
        collision_map;
    // Para mandarsela a los clientes.
    nlohmann::json visual_map_info;
    // Clave: id de entidad, valor: puntero a la entidad
    EntityMap entity_map;
    // Clave: id de cliente, valor: id de entidad del jugador.
    ClientMap client_map;

    // Devuelve la posicion no-colisionable mas cercana.
    position_t get_nearest_free_position(position_t position);
    /* Indica si la posicion indicada tiene un elemento colisionable (no se
     * puede pisar). */
    bool collides(position_t position);

    uint32_t
    get_next_id();  // Devuelve el siguiente id a asignar a una nueva entidad.

    /* Agrega una nueva entidad asociada al entity_id en la posicion indicada.*/
    void add_entity(Entity* entity, position_t position);

   public:
    Map(nlohmann::json map_info);
    ~Map();
    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(uint32_t entity_id, steps_t steps);

    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    uint32_t add_player(uint32_t client_id, nlohmann::json player_info);

    /* Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.*/
    void update(uint64_t delta_t);

    Player& get_player(uint32_t client_id);

    nlohmann::json get_position_data();
    nlohmann::json get_entity_data();
    nlohmann::json get_map_data();
};

#endif