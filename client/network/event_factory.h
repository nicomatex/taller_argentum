#ifndef __EVENT_FACTORY_H
#define __EVENT_FACTORY_H
#include <string>
#include <vector>

#include "../../include/event.h"
#include "../../include/types.h"

#ifndef MOVEMENT_ACTION_T
#define MOVEMENT_ACTION_T
enum mov_action_t { START, STOP };
#endif

#ifndef DIRECTION_T
#define DIRECTION_T
enum direction_t { UP, DOWN, LEFT, RIGHT };
#endif

class EventFactory {
   public:
    EventFactory();
    ~EventFactory();

    /**
     * @brief Evento de conexion.
     * 
     * @param character_name Nombre del personaje
     * @param password Contrasenia. No usada por ahora.
     * @return Event 
     */
    static Event connect_event(std::string character_name,
                               std::string password);

    /**
     * @brief Evento de chat
     * 
     * @param message Mensaje o comando a enviar
     * @param target_x Coordenada X del target en el mapa.
     * @param target_y Coordenada Y del target en el mapa.
     * @param inventory_slot Slot del inventario seleccionado.
     * @return Event 
     */
    static Event chat_event(std::string message, int target_x, int target_y,
                            int inventory_slot);

    /* Evento de movimiento. Recibe si se esta comenzando o finalizando el
    movimiento y en que direccion.*/

    /**
     * @brief Evento de movimiento.
     * 
     * @param action Accion (empezar o detener)
     * @param direction Direccion del movimiento.
     * @return Event 
     */
    static Event movement_event(mov_action_t action, direction_t direction);

    /**
     * @brief Evento de desconexion
     * 
     * @return Event 
     */
    static Event disconnect();

    /**
     * @brief Evento de ataque
     * 
     * @return Event 
     */
    static Event attack_event();


    /**
     * @brief Evento de uso del inventario.
     * 
     * @param slot Slot sobre el cual ejecutar la accion.
     * @return Event 
     */
    static Event inventory_event(SlotId slot);



    /**
     * @brief Evento de creacion de personaje
     * 
     * @param name Nombre del personaje
     * @param class_type Clase del personaje
     * @param race_type Raza del personaje
     * @return Event 
     */
    static Event create_event(std::string name, class_type_t class_type,
                              race_type_t race_type);

    /**
     * @brief Evento de levantar items del suelo.
     * 
     * @return Event 
     */
    static Event pickup_event();

    /**
     * @brief Evento de tirar un item al suelo
     * 
     * @param slot Slot del cual se desea tirar un item.
     * @return Event 
     */
    static Event drop_item_event(int slot);
};

#endif