#ifndef CLIENTS_NAMES_MONITOR_H
#define CLIENTS_NAMES_MONITOR_H

#include <mutex>
#include <unordered_map>
#include <utility>

#include "../include/types.h"

/**
 * @brief Bimap construido con `std::pair` para conectar
 * (`ClientId`)clients<->(`std::string`)names
 *
 * Construye un mapa bidireccional que permite conectar nombres a clientes y
 * viceversa. Se puede acceder a cada uno con los operadores `first` y `second`
 * de `std::pair`.
 *
 */
typedef std::pair<std::unordered_map<ClientId, std::string>,
                  std::unordered_map<std::string, ClientId>>
    ClientsNames;

/**
 * @brief Monitor de ClientsNames
 *
 */
class ClientsNamesMonitor {
   private:
    std::mutex m;
    ClientsNames clients_names;

   public:
    ClientsNamesMonitor();
    ~ClientsNamesMonitor();

    /**
     * @brief Agregar un cliente,nombre al mapa de clients<->names
     *
     * @param client_id
     * @param name
     */
    void add_name(ClientId client_id, const std::string& name);

    /**
     * @brief Eliminar un cliente,nombre del mapa de clients<->names
     *
     * @param client_id
     */
    void rm_name(ClientId client_id);

    /**
     * @brief Obtener un ClientId a partir de su nombre
     *
     * @param name
     * @return ClientId
     */
    ClientId get_client(const std::string& name);

    /**
     * @brief Obtener un nombre a partir del ClientId
     *
     * @param client_id
     * @return const std::string&
     */
    const std::string& get_name(ClientId client_id);
};

#endif  // CLIENTS_NAMES_MONITOR_H
