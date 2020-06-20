#ifndef __MAP_CHANGE_BUFFER_H
#define __MAP_CHANGE_BUFFER_H
#include <condition_variable>
#include <mutex>

#include "../nlohmann/json.hpp"

class MapChangeBuffer {
   private:
    std::mutex m;
    std::condition_variable cv;
    nlohmann::json map_info;
    unsigned int follow_entity_id;
    
    bool map_info_ready;

    bool entity_info_ready;

   public:
    MapChangeBuffer();
    ~MapChangeBuffer();
    /* Duerme el thread llamante hasta que la informacion este disponible.*/
    void wait_for_map();

    /* Llena el buffer con map info. */
    void set_map_info(nlohmann::json map_info);

    /* Setea el id de follow entity del buffer. */
    void set_follow_entity_id(unsigned int follow_entity_id);

    /* Devuelve la informacion de mapa guardada en el buffer.*/
    nlohmann::json get_map_info();

    /* Devuelve el id de entidad a seguir guardado en el buffer. */
    int get_follow_entity_id();

    /* Reinicia el buffer. */
    void reset();

};

#endif