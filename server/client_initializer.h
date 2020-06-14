#ifndef CLIENT_INITIALIZER_H
#define CLIENT_INITIALIZER_H

#include "server_manager.h"
#include "th_event_handler.h"

class ClientInitializeHandler : public ThEventHandler {
   private:
    ServerManager& server_manager;

   protected:
    void run_handler() override {
        // TODO: cambiar a json[]
        int client_id = event.get_client_id();
        std::string name = event.get_name();
        /*
        TODO: incluye crear archivos ejemplo de persistencia
        - lectura de disco
        - creación de json con información de la entidad
        */
        // Como primer aproximación, hardcodear un json:
        /*
        nombre: string
        mapa: id
        posicion: {x,y}
        id_cabeza:
        id_cuerpo:
        */

        server_manager.add_player(map_id, client_id, player_info);
    }

   public:
    ClientInitializeHandler(Event ev, ServerManager& server_manager)
        : ThEventHandler(ev), server_manager(server_manager) {}

    ~ClientInitializeHandler() {}
};

#endif  // CLIENT_INITIALIZER_H
