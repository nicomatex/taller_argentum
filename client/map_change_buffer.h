#ifndef __MAP_CHANGE_BUFFER_H
#define __MAP_CHANGE_BUFFER_H
#include <condition_variable>
#include <mutex>

#include "../include/nlohmann/json.hpp"

/**
 * @brief Buffer donde se almacenan los mapas al inicializar, asi como 
 * informacion de la entidad que representa al jugador.
 * 
 */
class MapChangeBuffer {
   private:
    std::mutex m;
    std::condition_variable cv;
    nlohmann::json map_info;
    unsigned int follow_entity_id;
    bool ready;

   public:
    MapChangeBuffer();
    ~MapChangeBuffer();
    
    /* Llena el buffer con map info. */
    /**
     * @brief Llena el buffer con nueva informacion para generar un nuevo mapa
     * y un id de entidad nuevo.
     * 
     * @param map_info Informacion de mapa [Generada por Tiled]
     * @param follow_entity_id id de la entidad que la camara debe seguir.
     */
    void fill(nlohmann::json map_info, unsigned int follow_entity_id);

    /**
     * @brief Devuelve la informacion almacenada en el mapa.
     * 
     * @return nlohmann::json 
     */
    nlohmann::json get_map_info();

    /**
     * @brief Devuelve el id de la entidad que se debe seguir.
     * 
     * @return int 
     */
    int get_follow_entity_id();

    /**
     * @brief Reinicia el buffer.
     * 
     */
    void reset();
};

#endif