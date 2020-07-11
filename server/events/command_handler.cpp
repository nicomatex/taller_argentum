#include "command_handler.h"

#include <stdexcept>

#include "../../include/nlohmann/json.hpp"
#include "../events/event_factory.h"
#include "../map_monitor.h"
#include "../server_manager.h"

#define COMMAND '/'
#define WHISPER '@'
#define HELP_MESSAGE "[info] Comando de ayuda!"

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
        } else if (cmd[0] == "tomar") {
            cmd_type = CMD_PICKUP;
        } else if (cmd[0] == "tirar") {
            cmd.push_back(line.substr(space, line.find(space + 1, line.npos)));
            cmd_type = CMD_DROP;
        } else if (cmd[0] == "revivir") {
            cmd_type = CMD_RESUSCITATE;
        } else if (cmd[0] == "curar") {
            cmd_type = CMD_HEAL;
        } else if (cmd[0] == "desequipar") {
            cmd_type = CMD_UNEQUIP;
        } else if (cmd[0] == "salir") {
            cmd_type = CMD_DISCONNECT;
        } else if (cmd[0] == "ayuda") {
            cmd_type = CMD_HELP;
        } else {
            throw CommandErrorException();
        }
    } else {
        cmd_type = CMD_MESSAGE;
        cmd.push_back(line);
    }
}

void CommandHandler::cmd_whisper(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    std::string chat_msg;
    try {
        chat_msg = "[susurro de] " +
                   server_manager.get_name_by_client(client_id) + ": " + cmd[1];
        server_manager.send_to(server_manager.get_client_by_name(cmd[0]),
                               EventFactory::chat_message(chat_msg));
        chat_msg = "[susurro a] " + cmd[0] + ": " + cmd[1];
        server_manager.send_to(client_id, EventFactory::chat_message(chat_msg));
    } catch (const ClientDisconnectedException& e) {
        chat_msg = "[info] El cliente '" + cmd[0] +
                   "' al que se le quiso enviar un mensaje" +
                   " esta desconectado.";
        server_manager.send_to(client_id, EventFactory::chat_message(chat_msg));
    }
}

void CommandHandler::cmd_message(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    Session& session = server_manager.get_session(client_id);
    std::string chat_msg = "[todos] " +
                           server_manager.get_name_by_client(client_id) + ": " +
                           cmd[0];
    session.broadcast(EventFactory::chat_message(chat_msg));
}

void CommandHandler::cmd_help(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.send_to(client_id, EventFactory::chat_message(HELP_MESSAGE));
}

void CommandHandler::cmd_disconnect(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.send_to(client_id, EventFactory::disconnect());
    server_manager.drop_client(client_id);
}

void CommandHandler::cmd_pickup(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::pickup_event(client_id));
}

void CommandHandler::cmd_drop(ClientId client_id, SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = 1;
    if (cmd.size() > 1) {
        try {
            amount = std::stoul(cmd[1]);
        } catch (const std::invalid_argument& e) {
            throw CommandErrorException();
        } catch (const std::out_of_range& e) {
            amount = UINT32_MAX;
        }
    }
    server_manager.dispatch(EventFactory::drop_event(client_id, slot, amount));
}

void CommandHandler::cmd_unequip_all(ClientId client_id) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::unequip_all_event(client_id));
}

void CommandHandler::cmd_resuscitate(ClientId client_id, position_t target) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::resuscitate_event(client_id, target));
}

void CommandHandler::cmd_heal(ClientId client_id, position_t target) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::heal_event(client_id, target));
}

void CommandHandler::handle(Event& event) {
    nlohmann::json json = event.get_json();
    try {
        std::string msg = json["msg"];
        parse_line(msg);

        switch (cmd_type) {
            case CMD_WHISPER:
                if (space == msg.npos)
                    // No hay un mensaje, lo recibido es '@{nombre}'
                    throw CommandErrorException();
                cmd_whisper(json["client_id"]);
                break;
            case CMD_MESSAGE:
                cmd_message(json["client_id"]);
                break;
            case CMD_HELP:
                cmd_help(json["client_id"]);
                break;
            case CMD_PICKUP:
                cmd_pickup(json["client_id"]);
                break;
            case CMD_DROP:
                cmd_drop(json["client_id"], json["slot"]);
                break;
            case CMD_RESUSCITATE:
                cmd_resuscitate(json["client_id"], json["target"]);
                break;
            case CMD_HEAL:
                cmd_heal(json["client_id"], json["target"]);
                break;
            case CMD_DISCONNECT:
                cmd_disconnect(json["client_id"]);
                break;
            case CMD_UNEQUIP:
                cmd_unequip_all(json["client_id"]);
                break;
            default:
                throw CommandErrorException();
                break;
        }
    } catch (const CommandErrorException& e) {
        ServerManager::get_instance().send_to(
            json["client_id"],
            EventFactory::chat_message("[info] " + std::string(e.what())));
    } catch (const std::exception& e) {
        std::cerr << "Observer: error during line parse.\n";
    }
    space = 0;
    cmd = std::vector<std::string>();
}

CommandHandler::CommandHandler() : BlockingThEventHandler(), space(0) {
    std::cerr << "CommandHandler: starting.." << std::endl;
}
CommandHandler::~CommandHandler() {}
