#ifndef MAP_TRANSITIONS_H
#define MAP_TRANSITIONS_H

#include <queue>
#include <unordered_map>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "position.h"

typedef struct map_change {
    std::string name;
    MapId map;
    position_t position;
} map_change_t;

/**
 * @brief Clase que se encarga de manejar las transiciones en cada mapa.
 *
 * Mantiene estructuras inicializadas durante el constructor que definen cuáles
 * son las posiciones del mapa que refieren a transiciones y cuando se ejecuta
 * un movimiento en el mapa (particularmente solo de jugadores) se encola en
 * caso de ser una "transicion". Cada transición es encolada con información del
 * nombre del personaje, el mapa y posición de destino.
 *
 */
class MapTransitions {
   private:
    MapId map_id;
    std::queue<map_change_t> changes_queue;
    /**
     * @brief Mapa de transiciones inicializado durante el constructor.
     *
     * Este mapa asocia posiciones del mapa con pares del tipo: id de mapa,
     * posición de destino.
     *
     */
    std::unordered_map<position_t, std::pair<MapId, position_t>, PositionHasher,
                       PositionComparator>
        teleports;

   public:
    MapTransitions(MapId map_id, nlohmann::json changes, int width, int height);
    ~MapTransitions();

    /**
     * @brief Agrega la transición en caso de ser necesaria de un jugador.
     *
     * Verifica si la posición a donde se va a mover el personaje es una
     * transición del mapa.
     *
     * @param name Nombre del personaje.
     * @param position Posición a donde se va a mover el personaje.
     */
    void push_if_transition(std::string name, position_t position);

    /**
     * @brief Agregar una transición forzada de un jugador a una posición de
     * destino en el mismo mapa.
     *
     * @param name Nombre del personaje.
     * @param dest Posición de destino.
     */
    void teleport(std::string name, position_t dest);

    std::queue<map_change_t>& get_changes();
};

#endif  // MAP_TRANSITIONS_H
