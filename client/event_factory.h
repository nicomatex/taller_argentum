#ifndef __EVENT_FACTORY_H
#define __EVENT_FACTORY_H

#include <string>
#include <vector>

#include "../include/event.h"

enum movement_action_t { START, STOP };

#ifndef DIRECTION_T
#define DIRECTION_T
enum direction_t { UP, DOWN, LEFT, RIGHT };
#endif

class EventFactory {
   public:
    EventFactory();
    ~EventFactory();

    /* Evento inicial para obtener la informacion del personaje solicitado. */
    static Event connect_event(std::string character_name,
                               std::string password);

    /* Evento del chat. */
    static Event chat_event(std::string message);

    /* Evento de movimiento. Recibe si se esta comenzando o finalizando el
    movimiento y en que direccion.*/
    static Event movement_event(movement_action_t action,
                                direction_t direction);

    /* Evento de desconexion*/
    static Event drop_event();
};

#endif