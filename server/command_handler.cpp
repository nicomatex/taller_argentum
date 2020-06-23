#include "command_handler.h"

#include "../nlohmann/json.hpp"
#include "event_factory.h"
#include "map_monitor.h"
#include "server_manager.h"

#define COMMAND '/'
#define WHISPER '@'
#define HELP_MESSAGE "Comando de ayuda!"

#include <stdexcept>

class CommandErrorException : public std::exception {
   private:
    const char help_msg[100] =
        "Commando invalido, escriba '/ayuda' para ayuda.";

   public:
    CommandErrorException() {}
    ~CommandErrorException() {}

    const char* what() const noexcept override {
        return help_msg;
    }
};

void CommandHandler::parse_line(const std::string& line) {
    if (line[0] == COMMAND || line[0] == WHISPER) {
        space = line.find(' ', 0);
        cmd.push_back(line.substr(1, space - 1));
        if (line[0] == WHISPER) {
            cmd_type = CMD_WHISPER;
            cmd.push_back(line.substr(space + 1, line.npos));
            return;
        } else if (cmd[0] == "salir") {
            cmd_type = CMD_DISCONNECT;
        } else if (cmd[0] == "ayuda") {
            cmd_type = CMD_DISCONNECT;
        } else {
            throw CommandErrorException();
        }
    } else {
        cmd_type = CMD_MESSAGE;
        cmd.push_back(line);
    }
}

void CommandHandler::run_handler() {
    nlohmann::json json = event.get_json();
    try {
        std::string msg = json["msg"];
        parse_line(msg);

        ServerManager& server_manager = ServerManager::get_instance();
        Session& session = server_manager.get_session(json["client_id"]);
        std::string chat_msg;

        switch (cmd_type) {
            case CMD_WHISPER:
                if (space == msg.npos)
                    throw CommandErrorException();
                try {
                    chat_msg =
                        "[susurro de] " +
                        server_manager.get_name_by_client(json["client_id"]) +
                        ": " + cmd[1];
                    server_manager.send_to(
                        server_manager.get_client_by_name(cmd[0]),
                        EventFactory::chat_message(chat_msg));
                    chat_msg = "[susurro a] " + cmd[0] + ": " + cmd[1];
                    server_manager.send_to(
                        json["client_id"],
                        EventFactory::chat_message(chat_msg));
                } catch (const ClientDisconnectedException& e) {
                    std::string msg = "El cliente '" + cmd[0] +
                                      "' al que se le quiso enviar un mensaje" +
                                      " esta desconectado.";
                    server_manager.send_to(json["client_id"],
                                           EventFactory::chat_message(msg));
                    break;
                }

                break;
            case CMD_MESSAGE:
                chat_msg =
                    "[todos] " +
                    server_manager.get_name_by_client(json["client_id"]) +
                    ": " + cmd[0];
                session.broadcast(EventFactory::chat_message(chat_msg));
                break;
            case CMD_HELP:
                server_manager.send_to(
                    json["client_id"],
                    EventFactory::chat_message(HELP_MESSAGE));
                break;
            case CMD_DISCONNECT:
                server_manager.send_to(json["client_id"],
                                       EventFactory::disconnect());
                server_manager.get_dispatcher().push_event(
                    EventFactory::drop_client(json["client_id"]));
                break;
            default:
                throw CommandErrorException();
                break;
        }
    } catch (const CommandErrorException& help) {
        ServerManager::get_instance().send_to(
            json["client_id"], EventFactory::chat_message(help.what()));
    }
}

CommandHandler::CommandHandler(Event ev) : ThEventHandler(ev), space(0) {}
CommandHandler::~CommandHandler() {}
