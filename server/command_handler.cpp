#include "command_handler.h"

#include "../nlohmann/json.hpp"
#include "event_factory.h"
#include "map_monitor.h"
#include "server_manager.h"

#define COMMAND '/'
#define WHISPER '@'

void CommandHandler::parse_line(const std::string& line) {
    // Cambiar esta linea
    cmd_type = CMD_MESSAGE;
    if (line[0] == COMMAND) {
        cmd.push_back(std::string(++line.begin(), line.end()));
    } else if (line[0] == WHISPER) {
        cmd.push_back(std::string(++line.begin(), line.end()));
    } else {
        cmd.push_back(line);
    }
}

void CommandHandler::run_handler() {
    nlohmann::json json = event.get_json();
    parse_line(json["msg"]);

    ServerManager& server_manager = ServerManager::get_instance();

    switch (cmd_type) {
        case CMD_WHISPER:
            // response["msg"] =
            //     server_manager.get_player_name(json["client_id"]) + cmd[1];
            // server_manager.send_to(server_manager.get_client_id(cmd[0]),
            // Event());
            break;
        default:
            Session& session = server_manager.get_session(json["client_id"]);
            session.broadcast(EventFactory::chat_message(cmd[0]));
            break;
    }
}

CommandHandler::CommandHandler(Event ev) : ThEventHandler(ev) {}
CommandHandler::~CommandHandler() {}
