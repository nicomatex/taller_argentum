#ifndef __MAP_H
#define __MAP_H

#include <cstdint>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "actions/action.h"
#include "entities/entity.h"
#include "entities/entity_factory.h"
#include "items/item.h"
#include "map_log_factory.h"
#include "map_transitions.h"
#include "monster_spawner.h"
#include "position.h"

#define MAP_SIZE 50

class Player;

typedef struct entity_action {
    EntityId entity;
    Action* action;
} entity_action_t;

template <typename T>
using ObjectMatrix =
    std::unordered_map<position_t, T, PositionHasher, PositionComparator>;

// clave: id de entidad, valor: position_t
typedef std::unordered_map<EntityId, position_t> PositionMap;

// Clave: position_t, valor: puntero a una entidad
typedef ObjectMatrix<Entity*> EntityMatrix;

// Clave: position_t. Contiene los bloques colisionables del mapa
typedef std::unordered_set<position_t, PositionHasher, PositionComparator>
    PositionSet;

// Clave: position_t, valor: puntero a un item
typedef ObjectMatrix<Item*> LootMatrix;

class Map {
   private:
    friend class Action;
    friend class MonsterSpawner;
    int width;
    int height;

    PositionMap position_map;
    bool _dirty_entities;
    EntityMatrix entity_matrix;
    bool _dirty_loot;
    LootMatrix loot_matrix;

    PositionSet collision_map;
    // PositionSet safe_zone;

    MapTransitions transitions;
    EntityFactory entity_factory;
    MonsterSpawner monster_spawner;

    std::queue<entity_action_t> actions;
    std::queue<map_log_t> update_logs;

    // Para mandarsela a los clientes.
    nlohmann::json visual_map_info;

    // Devuelve la posicion no-colisionable mas cercana.
    template <typename T>
    position_t get_nearest_free_position(ObjectMatrix<T> object_matrix,
                                         position_t position);

    /* Indica si la posicion indicada tiene un elemento colisionable (no se
     * puede pisar). */
    template <typename T>
    bool collides(ObjectMatrix<T> object_matrix, position_t position);

    /* Agrega una nueva entidad asociada al entity_id en la posicion indicada.*/
    void add_entity(Entity* entity, position_t position);

   public:
    Map(const nlohmann::json& map_description, const nlohmann::json& map_mobs,
        const nlohmann::json& map_transitions);
    ~Map();

    Map(const Map& other);
    Map& operator=(const Map& other);

    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(EntityId entity_id, position_t steps);

    std::queue<map_change_t>& get_transitions();

    /* Devuelve el id de entidad asignado dentro del mapa al jugador. */
    nlohmann::json add_player(nlohmann::json player_info);

    nlohmann::json rm_player(EntityId entity_id);

    void rm_entity(EntityId entity_id);

    position_t get_position(EntityId entity_id);

    position_t get_nearest_entity_pos(position_t entity_pos,
                                      unsigned int distance,
                                      entity_type_t entity_type);

    bool entity_exists(EntityId entity_id);

    /* Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.*/
    void update(uint64_t delta_t);

    /* Agrega un log de accion al mapa */
    void push_log(const map_log_t& log);

    /* Ejecuta sobre la entidad asociada al id la accion. */
    void push_action(EntityId entity_id, Action* action);

    void drop_loot(EntityId entity_id, Item* item);
    void drop_loot(EntityId entity_id, const std::vector<Item*>& item);
    Item* pickup_loot(EntityId entity_id);

    static nlohmann::json get_position_data(const PositionMap& position_map);
    const PositionMap get_position_map() const;

    bool dirty_entities() const;
    nlohmann::json get_entity_data();
    bool dirty_loot() const;
    nlohmann::json get_loot_data();

    std::queue<map_log_t>& get_update_logs();
    nlohmann::json get_map_data();
};

#endif