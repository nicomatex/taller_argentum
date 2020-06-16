#ifndef __PLAYER_H
#define __PLAYER_H
#include <string>

#include "entity.h"
#include "map.h"

class Player : public Entity {
   private:
    unsigned int player_speed;  // en tiles per second
    int current_speed_x;        // es 1, -1 o 0
    int current_speed_y;        // es 1, -1 o 0
    int move_accumulator;
    int head_id;
    int body_id;
    std::string name;

    Map &map;  // Mapa en el que esta el jugador en este momento.
               // STATS
               // INVENTARIO
   public:
    Player(int entity_id, int head_id, int body_id, std::string name,
           Map &map);  // Aca probablemente habria que pasarle mas info, como el
                       // nombre
                       // y los stats. Por lo pronto con el id y el map tamos
    entity_type_t get_type() override;
    void set_current_speed(int value_x, int value_y);
    void update(uint64_t delta_t) override;
};

#endif