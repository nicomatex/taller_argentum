#include "command_handler.h"

#include <limits>
#include <sstream>
#include <stdexcept>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
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
    bool ok = true;
    if (line[0] == COMMAND || line[0] == WHISPER) {
        if (line[0] == WHISPER) {
            space = line.find(' ', 0);
            cmd.push_back(line.substr(1, space - 1));
            cmd.push_back(line.substr(space + 1, line.npos));
            cmd_type = CMD_WHISPER;
            return;
        }
        std::istringstream iss(line);
        std::string s;
        while (getline(iss, s, ' ')) {
            cmd.push_back(s);
        }
        if (cmd[0] == "/tomar") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_PICKUP;
        } else if (cmd[0] == "/tirar") {
            if (cmd.size() > 2)
                ok = false;
            cmd_type = CMD_DROP;
        } else if (cmd[0] == "/revivir") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_RESUSCITATE;
        } else if (cmd[0] == "/curar") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_HEAL;
        } else if (cmd[0] == "/desequipar") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_UNEQUIP;
        } else if (cmd[0] == "/salir") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_DISCONNECT;
        } else if (cmd[0] == "/ayuda") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_HELP;
        } else if (cmd[0] == "/vender") {
            if (cmd.size() > 2)
                ok = false;
            cmd_type = CMD_SELL;
        } else if (cmd[0] == "/comprar") {
            if (cmd.size() != 2 && cmd.size() != 3)
                ok = false;
            cmd_type = CMD_BUY;
        } else if (cmd[0] == "/listar") {
            if (cmd.size() != 1)
                ok = false;
            cmd_type = CMD_LIST;
        } else {
            throw CommandErrorException();
        }
    } else {
        cmd_type = CMD_MESSAGE;
        cmd.push_back(line);
    }
    if (!ok)
        throw CommandErrorException();
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

void CommandHandler::cmd_list(ClientId client_id, position_t target) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::list_event(client_id, target));
}

// comprar <SlotId> <cantidad> o comprar <SlotId> donde cantidad es 1 por
// default
void CommandHandler::cmd_buy(ClientId client_id, position_t target) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = 1;
    uint32_t slot = 0;
    try {
        slot = std::stoul(cmd[1]);
        if (amount > std::numeric_limits<SlotId>::max())
            throw CommandErrorException();  // My myexception diciendo lo que
                                            // esta mal, o usamos la de
                                            // inventory
        if (cmd.size() == 3)
            amount = std::stoul(cmd[2]);
    } catch (const std::invalid_argument& e) {
        throw CommandErrorException();
    } catch (const std::out_of_range& e) {
        amount = UINT32_MAX;
    }
    server_manager.dispatch(EventFactory::buy_event(client_id, target, (SlotId)slot, amount));
}

// vender <cantidad> o vender donde cantidad es por default 1
void CommandHandler::cmd_sell(ClientId client_id, position_t target,
                              SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = 1;
    if (cmd.size() == 2) {
        try {
            amount = std::stoul(cmd[1]);
        } catch (const std::invalid_argument& e) {
            throw CommandErrorException();
        } catch (const std::out_of_range& e) {
            amount = UINT32_MAX;
        }
    }
    server_manager.dispatch(
        EventFactory::sell_event(client_id, target, slot, amount));
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
            case CMD_LIST:
                cmd_list(json["client_id"], json["target"]);
                break;
            case CMD_SELL:
                cmd_sell(json["client_id"], json["target"], json["slot"]);
                break;
            case CMD_BUY:
                cmd_buy(json["client_id"], json["target"]);
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
