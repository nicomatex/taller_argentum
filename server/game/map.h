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
    bool _is_safe;
    std::string map_name;

    position_t healer_pos;
    PositionMap position_map;
    bool _dirty_entities;
    EntityMatrix entity_matrix;
    bool _dirty_loot;
    LootMatrix loot_matrix;

    PositionSet collision_map;

    MapTransitions transitions;
    EntityFactory entity_factory;
    MonsterSpawner monster_spawner;

    std::queue<entity_action_t> actions;
    std::queue<map_log_t> update_logs;

    // Para mandarsela a los clientes.
    nlohmann::json visual_map_info;

    /**
     * @brief Devuelve la posicion no-colisionable mas cercana.
     *
     * @tparam T Tipo de objeto: Items o Entidades.
     * @param object_matrix Matriz de tipo ObjectMatrix especializada en T.
     * @param position Posición origen.
     * @return position_t Posición más cercana encontrada.
     */
    template <typename T>
    position_t get_nearest_free_position(ObjectMatrix<T> object_matrix,
                                         position_t position);

    /**
     * @brief Indica si la posicion indicada tiene un elemento colisionable.
     *
     * @tparam T Tipo de objeto: Items o Entidades.
     * @param object_matrix Matriz de tipo ObjectMatrix especializada en T.
     * @param position Posición a comprobar si colisiona.
     * @return true
     * @return false
     */
    template <typename T>
    bool collides(ObjectMatrix<T> object_matrix, position_t position);

    /**
     * @brief Agrega una nueva entidad asociada al entity_id en la posicion
     * indicada.
     *
     * @param entity Entidad a ser agregada.
     * @param position Posición a donde se quiere agregar la entidad.
     */
    void add_entity(Entity* entity, position_t position);

    /**
     * @brief Elimina a una entidad del mapa.
     *
     * @param entity_id Id de entidad.
     */
    void rm_entity(EntityId entity_id);

   public:
    Map(MapId map_id, const std::string& map_name, bool is_safe,
        const nlohmann::json& map_description, const nlohmann::json& map_mobs,
        const nlohmann::json& map_transitions);
    ~Map();

    Map(const Map& other) = delete;

    const std::string& get_name();

    /**
     * @brief Mueve la entidad asociada al entity_id hacia la posicion relativa
     * steps.
     *
     * @param entity_id Id de entidad a mover.
     * @param steps Posición relativa a la entidad a donde se va a mover.
     */
    void move(EntityId entity_id, position_t steps);

    /**
     * @brief Obtiene la cola de transiciones del mapa.
     *
     * @return std::queue<map_change_t>& Referencia a la cola de transiciones.
     */
    std::queue<map_change_t>& get_transitions();

    /**
     * @brief Teletransporta a un jugador a través de una transición.
     *
     * @param player_id Id de entidad del jugador a teletransportar.
     * @param dest Posición destino.
     */
    void teleport(EntityId player_id, position_t dest);

    /**
     * @brief Agrega un jugador al mapa a partir de su información.
     *
     * @param player_info Información del jugador para agregarlo al mapa.
     * @return nlohmann::json Información del jugador actualizada luego de ser
     * agregado.
     */
    nlohmann::json add_player(nlohmann::json player_info);

    /**
     * @brief Eliminar a un jugador identificado por su id del mapa.
     *
     * @param entity_id Id de entidad del jugador a eliminar.
     * @return nlohmann::json Información necesaria para persistir al personaje
     * al ser sacado del mapa.
     */
    nlohmann::json rm_player(EntityId entity_id);

    position_t get_position(EntityId entity_id);

    position_t get_healer_pos() const;

    bool is_safe() const;

    /**
     * @brief Obtener la posición de la entidad de un tipo más cercana.
     *
     * @param entity_pos Posición orígen desde donde buscar.
     * @param distance Distancia máxima (Manhattan) a buscar la entidad.
     * @param entity_type Tipo de entidad buscada.
     * @return position_t Posición de una entidad del tipo buscada, o si no se
     * encontró, la misma posición orígen.
     */
    position_t get_nearest_entity_pos(position_t entity_pos,
                                      unsigned int distance,
                                      entity_type_t entity_type);

    /**
     * @brief Verificar si una entidad existe o no.
     *
     * @param entity_id Id de entidad a verificar si existe.
     * @return bool
     */
    bool entity_exists(EntityId entity_id);

    /**
     * @brief Actualiza todas las entidades que contiene segun el delta_t
     * transcurrido.
     *
     * @param delta_t Tiempo transcurrido (en microsegundos).
     */
    void update(uint64_t delta_t);

    /**
     * @brief Agrega un log al mapa.
     *
     * Los logs son ulitizados para enviar a los jugadores correspondientes
     * información específica según sus acciones recientes.
     *
     * @param log Log del mapa.
     */
    void push_log(const map_log_t& log);

    /**
     * @brief Ejecuta sobre la entidad asociada al id la accion.
     *
     * El mapa se encargará de liberar la memoria ocupada por la acción a través
     * de un `delete`.
     *
     * @param entity_id Id de entidad.
     * @param action Puntero a clase de tipo Accion alocada en el Heap.
     */
    void push_action(EntityId entity_id, Action* action);

    /**
     * @brief Deja el item pasado por parámetro en la posición de la entidad.
     *
     * @param entity_id Id de entidad que deja caer el item.
     * @param item Item transferido al mapa.
     */
    void drop_loot(EntityId entity_id, Item* item);

    /**
     * @brief Deja caer la lista de items en el mapa.
     *
     * @param entity_id Id de entidad que deja caer los items.
     * @param items Lista de items transferidos al mapa.
     */
    void drop_loot(EntityId entity_id, const std::vector<Item*>& items);

    /**
     * @brief Intenta obtener de la posición donde se encuentra la entidad el
     * item que haya allí.
     *
     * @param entity_id Id de entidad que intenta obtener el item.
     * @return Item* El item obtenido, `NULL` si no había nada en esa posición.
     */
    Item* pickup_loot(EntityId entity_id);

    /**
     * @brief Realizar una copia en forma de `json` de un mapa de posiciones.
     *
     * @param position_map Mapa de posiciones.
     * @return nlohmann::json Mapa de posiciones transformado a `json`.
     */
    static nlohmann::json get_position_data(const PositionMap& position_map);
    /**
     * @brief Obtiene una copia del mapa de posiciones de las entidades.
     *
     * @return const PositionMap Lista de posiciones de entidades en el mapa.
     */
    const PositionMap get_position_map() const;

    /**
     * @brief Verificar si hubo un cambio en las entidades del mapa desde la
     * última vez que se utilizó este método.
     *
     * @return true Se agregó o eliminó alguna entidad.
     * @return false No se agregó o eliminó ninguna entidad.
     */
    bool dirty_entities() const;
    /**
     * @brief Obtiene la información de las entidades del mapa.
     *
     * @return nlohmann::json Lista de información de las entidades en el mapa.
     */
    nlohmann::json get_entity_data();

    /**
     * @brief Verificar si hubo un cambio en los items caidos en el mapa desde
     * la última vez que se utilizó este método.
     *
     * @return true Se agregó o eliminó algún item.
     * @return false No se agregó o eliminó ningún item.
     */
    bool dirty_loot() const;
    /**
     * @brief Obtiene la información de los items del mapa.
     *
     * @return nlohmann::json Lista de información y posiciones de los items en
     * el mapa.
     */
    nlohmann::json get_loot_data();

    /**
     * @brief Obtiene la cola de "logs" del mapa.
     *
     * @return std::queue<map_log_t>& Referencia a la cola de logs del mapa.
     */
    std::queue<map_log_t>& get_update_logs();

    /**
     * @brief Obtiene la información gráfica del mapa en forma de `json`.
     *
     * @return nlohmann::json Información gráfica del mapa.
     */
    nlohmann::json get_map_data();
};

#endif