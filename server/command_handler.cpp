#include "command_handler.h"

#include "../nlohmann/json.hpp"
#include "event_factory.h"
#include "map_monitor.h"
#include "server_manager.h"

#define COMMAND '/'
#define WHISPER '@'

void CommandHandler::parse_line(const std::string& line) {
    // Cambiar esta linea
    if (line[0] == COMMAND) {
        cmd_type = CMD_MESSAGE;
        cmd.push_back(std::string(++line.begin(), line.end()));
    } else if (line[0] == WHISPER) {
        cmd_type = CMD_WHISPER;
        size_t i = line.find(' ', 0);
        if (i == line.size()) {
            cmd_type = CMD_HELP;
            return;
        }
        cmd.push_back(line.substr(1, i - 1));
        cmd.push_back(line.substr(i + 1, line.npos));
    } else {
        cmd_type = CMD_MESSAGE;
        cmd.push_back(line);
    }
}

void CommandHandler::run_handler() {
    nlohmann::json json = event.get_json();
    parse_line(json["msg"]);

    ServerManager& server_manager = ServerManager::get_instance();
    std::string chat_msg;

    switch (cmd_type) {
        case CMD_WHISPER:
            chat_msg = "[susurro a] " + cmd[0] + ": " + cmd[1];
            server_manager.send_to(json["client_id"],
                                   EventFactory::chat_message(chat_msg));
            chat_msg = "[susurro de] " +
                       server_manager.get_name_by_client(json["client_id"]) +
                       ": " + cmd[1];
            server_manager.send_to(server_manager.get_client_by_name(cmd[0]),
                                   EventFactory::chat_message(chat_msg));
            break;
        case CMD_HELP:
            chat_msg = "Comando de ayuda!";
            server_manager.send_to(json["client_id"],
                                   EventFactory::chat_message(chat_msg));
        default:
            Session& session = server_manager.get_session(json["client_id"]);
            chat_msg = "[todos] " +
                       server_manager.get_name_by_client(json["client_id"]) +
                       ": " + cmd[0];
            session.broadcast(EventFactory::chat_message(chat_msg));
            break;
    }
}

CommandHandler::CommandHandler(Event ev) : ThEventHandler(ev) {}
CommandHandler::~CommandHandler() {}
