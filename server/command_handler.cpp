#include "command_handler.h"

#include "../nlohmann/json.hpp"
#include "map_monitor.h"
#include "server_manager.h"

#define COMMAND '/'
#define WHISPER '@'

void CommandHandler::parse_line(const std::string& line) {
    // Cambiar esta linea
    cmd_type = CMD_MESSAGE;
    if (line[0] == COMMAND) {
        cmd[0] = std::string(++line.begin(), line.end());
    } else if (line[0] == WHISPER) {
        cmd[0] = std::string(++line.begin(), line.end());
    } else {
        cmd[0] = line;
    }
}

void CommandHandler::run_handler() {
    nlohmann::json json = event.get_json();
    parse_line(json["command"]);

    ServerManager& server_manager = ServerManager::get_instance();
    nlohmann::json response;
    response["ev_id"] = 4;

    switch (cmd_type) {
        case CMD_WHISPER:
            // response["text"] =
            //     server_manager.get_player_name(json["client_id"]) + cmd[1];
            // server_manager.send_to(server_manager.get_client_id(cmd[0]),
            // Event());
            break;
        default:
            response["text"] = cmd[0];
            Session& session = server_manager.get_session(json["client_id"]);
            session.broadcast(Event(response));
            break;
    }
}

CommandHandler::CommandHandler(Event ev) : ThEventHandler(ev) {}
CommandHandler::~CommandHandler() {}
