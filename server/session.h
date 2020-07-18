#ifndef SESSION_H
#define SESSION_H

#include <mutex>

#include "../include/event.h"
#include "../include/types.h"
#include "game/map_monitor.h"
#include "network/client_id_set.h"
#include "network/th_broadcaster.h"
#include "th_observer.h"

class Session {
   private:
    /**
     * @brief Mapa protegido al que está asociada la sesión.
     *
     */
    MapMonitor& map;
    /**
     * @brief Mapeo protegido de Ids de clientes a Ids de entidades en el mapa
     * asociado a la sesión.
     *
     */
    ClientToEntityMap clients;
    /**
     * @brief Thread encargado de transmitir a todos los clientes.
     *
     */
    ThBroadcaster broadcaster;
    /**
     * @brief Thread encargado de observar y obtener las actualizaciones del
     * mapa asociado.
     *
     */
    ThObserver observer;

   public:
    Session(MapMonitor& map);

    void start();

    void finish();

    /**
     * @brief Agregar un cliente a la sesión.
     *
     * @param new_client Id del nuevo cliente.
     * @param entity_id Id de entidad asociada del mapa en el que se encuentra
     * el jugador del cliente.
     */
    void add_client(ClientId new_client, EntityId entity_id);

    EntityId rm_client(ClientId client_id);

    void push_action(ClientId client_id, Action* action);

    MapMonitor& get_map();

    /**
     * @brief Envía a todos los clientes en la sesión un evento.
     *
     * @param ev Evento a ser transmitido a todos los clientes.
     */
    void broadcast(const Event& ev);

    ~Session();
};

#endif  // SESSION_H
