#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <mutex>
#include <string>

#include "../include/network/socket_manager.h"
#include "../include/nlohmann/json.hpp"
#include "../include/types.h"
#include "character_manager.h"
#include "clients_names_monitor.h"
#include "game/game_manager.h"
#include "map_changer.h"
#include "network/clients_monitor.h"
#include "network/th_client_accepter.h"
#include "server_exceptions.h"
#include "session.h"
#include "th_dispatcher.h"

/**
 * @brief Orquestador de las componentes del servidor.
 *
 * Esta clase se encarga de contener las instancias de las distintas componentes
 * y contenedores necesarios para el servidor del juego. Esto incluye el manejo
 * de threads que se utilizan para el mismo.
 * Se encarga principalmente de la sincronización para agregar y sacar jugadores
 * de los diferentes mapas (y sesiones), esto incluye cuando un jugador cambia
 * de mapa o se teletransporta.
 *
 */
class ServerManager {
   private:
    /**
     * @brief Instancia única del GameManager.
     *
     */
    GameManager game_manager;
    /**
     * @brief Mutex para la sincronización del agregado o quitado de jugadores a
     * los diferentes mapas.
     *
     */
    std::recursive_mutex m;
    /**
     * @brief Instancia del thread aceptador de nuevos clientes.
     *
     */
    ThClientAccepter accepter;
    /**
     * @brief Instancia del CharacterManager, encargado de la persistencia de
     * los personajes.
     *
     */
    CharacterManager character_manager;
    /**
     * @brief Thread consumidor de los cambios de mapas.
     *
     */
    MapChanger map_changer;
    /**
     * @brief Contenedor de las sesiones del juego.
     *
     * La Sesiones son mapeadas según el Id de mapa al cual están asociadas.
     *
     */
    std::unordered_map<MapId, Session> sessions;
    /**
     * @brief Mapeo de Ids de clientes a Ids de mapas a los que está conectado
     * cada jugador.
     *
     */
    std::unordered_map<ClientId, MapId> client_to_map;
    /**
     * @brief Estructura protegida que asocia Ids de clientes con nombres de
     * personajes.
     *
     */
    ClientsNamesMonitor clients_names;
    /**
     * @brief Estructura protegida que mantiene la conexión (y threads) de cada
     * cliente.
     *
     */
    ClientsMonitor clients;
    /**
     * @brief "Dispatcher" de eventos del servidor.
     *
     */
    ThDispatcher dispatcher;

    /**
     * @brief Constructor privado del ServerManager, este es un "Singleton".
     *
     */
    ServerManager();

    MapMonitor& get_map_by_client(ClientId client_id);
    MapMonitor& get_map(MapId map_id);

   public:
    static ServerManager& get_instance();

    ThDispatcher& get_dispatcher();

    CharacterManager& get_character_manager();

    /**
     * @brief Agregar un evento que debe ser manejado por el servidor.
     *
     * Simplemente envía al "Dispatcher" el evento pasado por parámetro.
     *
     * @param ev Evento.
     */
    void dispatch(const Event& ev);

    /**
     * @brief Agregar a un cliente al servidor.
     *
     * @param client_id Id del nuevo cliente.
     * @param new_client Socket (alocado en heap) del nuevo cliente.
     */
    void add_client(ClientId client_id, SocketManager* new_client);
    /**
     * @brief Eliminar a un cliente del servidor.
     *
     * @param client_id Id del cliente a ser eliminado.
     */
    void rm_client(ClientId client_id);

    /**
     * @brief Función ejecutar la desconexión de un cliente.
     *
     * Esta función puede ser llamada porque un cliente desea desconectarse o es
     * pateado forzosamente del servidor.
     *
     * @param client_id Id del cliente a ser desconectado.
     */
    void drop_client(ClientId client_id);

    /**
     * @brief Agregar un jugador a un mapa y la sesión asociada.
     *
     * Para un cliente existente, agrega al jugador con la información
     * correspondiente.
     *
     * @param client_id Id del cliente que está entrando con un personaje.
     * @param player_info Información del personaje a ser agregado.
     */
    void add_player(ClientId client_id, nlohmann::json player_info);
    /**
     * @brief Remueve un jugador del mapa (y la sesión asociada) al que esté
     * conectado.
     *
     * @param client_id Id de cliente al que se va a remover.
     * @return nlohmann::json Devuelve la información del personaje que se
     * removió.
     */
    nlohmann::json rm_player(ClientId client_id);
    /**
     * @brief Cambia a un jugador de un mapa (y sesión) a otro.
     *
     * @param client_id Id de cliente que se está cambiando de mapa.
     * @param new_position Posición en el nuevo mapa.
     * @param new_map Id del mapa a donde se mueve el jugador.
     * @return nlohmann::json Devuelve la información del jugador al ser
     * cambiado de mapa.
     */
    nlohmann::json change_player_map(ClientId client_id,
                                     position_t new_position, MapId new_map);

    /**
     * @brief Envia un Evento a un cliente.
     *
     * @param client_id Id del cliente.
     * @param ev Evento a ser enviado al cliente.
     */
    void send_to(ClientId client_id, const Event& ev);

    std::string get_name_by_client(ClientId client_id);
    ClientId get_client_by_name(const std::string& name);

    /**
     * @brief Obtener la sesión a la que está conectado un cliente.
     *
     * @param client_id Id del cliente.
     * @return Session Sesión a la que está conectado un cliente.
     */
    Session& get_session(ClientId client_id);

    /**
     * @brief Cerrar y finalizar el servidor de forma ordenada.
     *
     * Esta función patea a todos los clientes (los desconecta y persiste sus
     * personajes), cierra todas las componentes y une todos los threads.
     *
     */
    void finish();

    ~ServerManager();
};

#endif  // SERVER_MANAGER_H
