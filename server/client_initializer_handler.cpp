#include "client_initializer_handler.h"

#include "map.h"
#include "position.h"
#include "server_manager.h"

ClientInitializeHandler::ClientInitializeHandler(Event ev)
    : ThEventHandler(ev) {}

ClientInitializeHandler::~ClientInitializeHandler() {}

void ClientInitializeHandler::run_handler() {
    ServerManager& server_manager = ServerManager::get_instance();
    /*
        TODO: incluye crear archivos ejemplo de persistencia
            - lectura de disco
            - creación de json con información de la entidad
    */
    /*
        DONE:
        Como primera aproximacion hardcodear el player:
            nombre: string
            mapa: id
            posicion: {x,y}
            id_cabeza:
            id_cuerpo:
    */

    nlohmann::json connect_info = event.get_json();
    std::string player_name = connect_info["player"]["name"];
    std::cout << "Entered ClientInitializerHandler\n";
    // Aca haría el lookup usando el name
    nlohmann::json player_info = {{"name", player_name},
                                  {"map", 0},
                                  {"pos", position_t{10, 10}},
                                  {"head_id", 2},
                                  {"body_id", 2}};
    int map_id = 0;
    server_manager.add_player(map_id, ClientId(connect_info["client_id"]),
                              player_info);
}