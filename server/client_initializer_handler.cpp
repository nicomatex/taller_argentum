#include "client_initializer_handler.h"
#include "map.h"

ClientInitializeHandler::ClientInitializeHandler(Event ev,
												 ServerManager& server_manager)
        				: ThEventHandler(ev), server_manager(server_manager) {}

ClientInitializeHandler::~ClientInitializeHandler() {}

void ClientInitializeHandler::run_handler() {
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
	//int client_id = event.get_client_id();
	std::string player_name = connect_info["player"]["name"];
	//Aca haría el lookup usando el name
	position_t player_pos{3,5};
	nlohmann::json player_info = {
		{"name", player_name},
		{"map", 0},
		{"position", player_pos},
        {"id_head", 2},
        {"id_body", 2}
	}; 
	int map_id = 1;
	server_manager.add_player(map_id, int(connect_info["client_id"]),
							  player_info);
}