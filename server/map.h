#ifndef __MAP_H
#define __MAP_H
#include <boost/functional/hash.hpp>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

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

class Map {
   private:
    std::mutex m;
    PositionMap position_map;
    std::unordered_set<int> entity_matrix[MAP_SIZE][MAP_SIZE];
    std::unordered_set<position_t, boost::hash<position_t>> collision_map;
    position_t get_nearest_free_position(position_t position);

    /* Indica si la posicion indicada tiene un elemento colisionable (no se
     * puede pisar). */
    bool collides(position_t position);

   public:
    Map();
    ~Map();
    /* Mueve la entidad asociada al entity_id un tile en la direccion
     * indicada.*/
    void move(unsigned int entity_id, steps_t steps);

    /* Agrega una nueva entidad asociada al entity_id en la posicion indicada.*/
    void add_entity(unsigned int entity_id, position_t position);

    /* Devuelve una copia del mapa de posiciones.*/
    PositionMap get_position_map();
};

#endif