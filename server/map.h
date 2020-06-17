#ifndef __MAP_H
#define __MAP_H

#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "entity.h"
#include "position.h"

#define MAP_SIZE 50

class Player;

typedef struct steps {
    int x;
    int y;
} steps_t;

// clave: id de entidad, valor: position_t
typedef std::unordered_map<EntityId, position_t> PositionMap;

// Clave: id de entidad, valor: puntero a la entidad
typedef std::unordered_map<EntityId, Entity*> EntityMap;

// Clave: id de cliente, valor: id de entidad del jugador.
typedef std::unordered_map<ClientId, EntityId> ClientMap;

// Clave: position_t. Contiene los bloques colisionables.
typedef std::unordered_set<position_t, PositionHasher, PositionComparator>
    CollisionMap;

class Map {
   private:
    std::mutex m;
    PositionMap position_map;
    // Set de ids de lo que hay en cada posicion.
    std::unordered_set<EntityId> entity_matrix[MAP_SIZE][MAP_SIZE];
    CollisionMap collision_map;
    EntityMap entity_map;
    ClientMap client_map;
    // Para mandarsela a los clientes.
    nlohmann::json visual_map_info;

    // Devuelve la posicion no-colisionable mas cercana.
    position_t get_nearest_free_position(position_t position);

    /* Indica si la posicion indicada tiene un elemento colisionable (no se
     * puede pisar). */
    bool collides(position_t position);

    // Devuelve el siguiente id a asignar a una nueva entidad.
    EntityId get_next_id();

    /* Agrega una nueva entidad asociada al entity_id en la posicion indicada.*/
    void add_entity(Entity* entity, position_t position);

   public:
    Map(nlohmann::json map_info);
    ~Map();
    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(EntityId entity_id, steps_t steps);

    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    EntityId add_player(ClientId client_id, nlohmann::json player_info);

    /* Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.*/
    void update(uint64_t delta_t);

    Player& get_player(ClientId client_id);

    nlohmann::json get_position_data();
    nlohmann::json get_entity_data();
    nlohmann::json get_map_data();
};

#endif