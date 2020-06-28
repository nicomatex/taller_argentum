#ifndef __MAP_H
#define __MAP_H

#include <cstdint>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "../include/types.h"
#include "../nlohmann/json.hpp"
#include "action.h"
#include "entity.h"
#include "map_changer.h"
#include "position.h"

#define MAP_SIZE 50

class Player;

typedef struct entity_action {
    EntityId entity;
    Action* action;
} entity_action_t;

// clave: id de entidad, valor: position_t
typedef std::unordered_map<EntityId, position_t> PositionMap;

// Clave: id de entidad, valor: puntero a la entidad
typedef std::unordered_map<EntityId, Entity*> EntityMap;

typedef std::unordered_map<position_t, Entity*, PositionHasher,
                           PositionComparator>
    EntityMatrix;

// Clave: position_t. Contiene los bloques colisionables.
typedef std::unordered_set<position_t, PositionHasher, PositionComparator>
    CollisionMap;

class Map {
   private:
    friend class Action;

    bool dirty;
    PositionMap position_map;
    // Set de ids de lo que hay en cada posicion.
    EntityMatrix entity_matrix;
    CollisionMap collision_map;
    EntityMap entity_map;
    MapChanger& map_changer;
    int height;
    int width;

    std::queue<entity_action_t> actions;
    std::queue<nlohmann::json> update_logs;

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

    void solve_combats();

   public:
    Map(nlohmann::json map_info, MapChanger& map_changer);
    ~Map();

    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(EntityId entity_id, position_t steps);

    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    EntityId add_player(nlohmann::json player_info);

    nlohmann::json rm_player(EntityId entity_id);

    position_t get_position(EntityId entity_id);

    EntityId get_entity_id(position_t position);

    /* Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.*/
    void update(uint64_t delta_t);

    /* */
    void push_log(const nlohmann::json& log);

    /* Ejecuta sobre la entidad asociada al id la accion. */
    void push_action(EntityId entity_id, Action* action);

    std::queue<nlohmann::json>& get_update_logs();
    static nlohmann::json get_position_data(const PositionMap& position_map);
    const PositionMap get_position_map() const;
    nlohmann::json get_entity_data();
    nlohmann::json get_map_data();
    bool is_dirty() const;
};

#endif