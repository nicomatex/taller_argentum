#ifndef CLIENTS_MONITOR_H
#define CLIENTS_MONITOR_H

#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "../../include/event.h"
#include "../../include/network/socket_exception.h"
#include "../../include/network/socket_manager.h"
#include "../../include/types.h"

/**
 * @brief Monitor de sockets de los clientes.
 *
 * Esta clase permite controlar los SocketManager asociados a un ClientId de
 * forma segura. Esto incluye enviar los eventos, detectar cuando un cliente se
 * desconecta o cuando se quiere desconectar alguno de ellos.
 *
 */
class ClientsMonitor {
   private:
    std::recursive_mutex m;
    std::unordered_map<ClientId, SocketManager*> clients;
    std::unordered_set<ClientId> connected_clients;

   public:
    ClientsMonitor();
    ~ClientsMonitor();

    void add_client(ClientId client_id, SocketManager* client);

    SocketManager* rm_client(ClientId client_id);

    /**
     * @brief Setea la desconexión de un cliente.
     *
     * Esta clase encola en el "Dispatcher" el evento exlusivo del servidor para
     * realizar la serie de acciones que implica desconectar a un cliente de
     * forma ordenada.
     *
     * @param client_id Id del cliente a ser desconectado.
     */
    void drop(ClientId client_id);

    /**
     * @brief Prepara a todos los clientes para la desconexión.
     *
     * Esto se hace repitiendo la acción de `drop` para todos los clientes. (Ver
     * el miembro `drop(ClientId)` de esta misma clase para más información)
     *
     */
    void drop_all();

    /**
     * @brief Envía un evento de forma segura a un cliente.
     *
     * Si el envío falla se desconecta de forma ordenada al cliente.
     *
     * @param client_id Id del cliente al que se le quiere enviar el evento.
     * @param ev Evento a ser enviado.
     */
    void send_to(ClientId client_id, Event ev);
};

#endif  // CLIENTS_MONITOR_H
