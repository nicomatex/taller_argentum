#include "command_handler.h"

#include <limits>
#include <sstream>
#include <stdexcept>

#include "../../include/nlohmann/json.hpp"
#include "../../include/types.h"
#include "../events/event_factory.h"
#include "../server_manager.h"

#define COMMAND '/'
#define WHISPER '@'

class CommandErrorException : public std::exception {
   private:
    const char help_msg[150] =
        "Comando invalido, escriba '/ayuda' para la lista de comandos, escriba "
        "'/ayuda <comando>' para una descripcion del comando.";

   public:
    CommandErrorException() {}
    ~CommandErrorException() {}

    const char* what() const noexcept override {
        return help_msg;
    }
};

const command_case_t CommandHandler::whisper = {
    "@",
    [](const std::vector<std::string>& cmd) -> bool { return cmd.size() == 2; },
    "[@<nombre>]: Enviar un susurro (mensaje privado) al jugador 'nombre'.",
    &CommandHandler::cmd_whisper};

const command_case_t CommandHandler::message = {
    "",
    [](const std::vector<std::string>& cmd) -> bool { return cmd.size() > 0; },
    "[mensaje]: Escribir libremente en la consola para enviar un mensaje a "
    "todos.",
    &CommandHandler::cmd_message};

const std::vector<command_case_t> CommandHandler::commands({
    {"/tomar",
     [](const std::vector<std::string>& cmd) -> bool {
         return cmd.size() == 1;
     },
     ": Tomar el objeto sobre el que esta parado tu personaje.",
     &CommandHandler::cmd_pickup},
    {"/tirar",
     [](const std::vector<std::string>& cmd) -> bool {
         return cmd.size() <= 2;
     },
     "(cantidad): Tirar (cantidad o 1) del objeto seleccionado de tu "
     "inventario.",
     &CommandHandler::cmd_drop},
    {"/resucitar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1);
     },
     ": Ejecuta este comando para que el cura mas cercano te resucite (O haz\n"
     "click sobre un cura cercano para recibir una resucitacion instantanea)",
     &CommandHandler::cmd_resuscitate},
    {"/curar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1);
     },
     ": Haz click sobre un Cura y luego ejecuta este comando para curar tus\n"
     "puntos de vida.",
     &CommandHandler::cmd_heal},
    {"/salir",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1);
     },
     ": Salir del juego. :(", &CommandHandler::cmd_disconnect},
    {"/ayuda",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1 || cmd.size() == 2);
     },
     "(comando): Listar los comandos posibles de la consola. O si se "
     "acompaia\n"
     "de un comando, mostrar su uso.",
     &CommandHandler::cmd_help},
    {"/vender",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() <= 2);
     },
     "(cantidad): Vender (cantidad o 1) del item seleccionado del inventario\n"
     "a un Comerciante (Se debe hacer click sobre uno previamente)",
     &CommandHandler::cmd_sell},
    {"/comprar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 2 || cmd.size() == 3);
     },
     "<posicion> (cantidad): Comprar (cantidad o 1) de la posicion a un\n"
     "Comerciante (Se debe hacer click sobre uno previamente)",
     &CommandHandler::cmd_buy},
    {"/listar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1);
     },
     ": Listar los objetos disponibles de un Banquero o Comerciante\n"
     "(se debe hacer click sobre alguno previamente)",
     &CommandHandler::cmd_list},
    {"/depositar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() <= 2);
     },
     " (cantidad): Depositar (cantidad o 1) items del slot seleccionado del "
     "inventario al banco.",
     &CommandHandler::cmd_deposit_item},
    {"/retirar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 2 || cmd.size() == 3);
     },
     "<posicion> (cantidad): Retirar (cantidad o 1) items del la posicion dada "
     "del banco.",
     &CommandHandler::cmd_withdraw_item},
    {"/depositaroro",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() <= 2);
     },
     ": (cantidad): Depositar (cantidad o 1) de oro al banco.",
     &CommandHandler::cmd_deposit_gold},
    {"/retiraroro",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() <= 2);
     },
     ": (cantidad): Retirar (cantidad o 1) de oro del banco.",
     &CommandHandler::cmd_withdraw_gold},
    {"/meditar",
     [](const std::vector<std::string>& cmd) -> bool {
         return (cmd.size() == 1);
     },
     ": Meditar restaura mana.", &CommandHandler::cmd_meditate},
});

void CommandHandler::parse_line(const std::string& line) {
    bool found = false;
    if (line[0] == COMMAND) {
        std::istringstream iss(line);
        std::string s;
        while (getline(iss, s, ' ')) {
            cmd.push_back(s);
        }
        for (auto& it : commands) {
            if (cmd[0] != it.cmd)
                continue;
            if (it.condition(cmd))
                found = true;
            current_command = it;
            break;
        }
    } else if (line[0] == WHISPER) {
        space = line.find(' ', 0);
        if (space != line.npos)
            found = true;
        cmd.push_back(line.substr(1, space - 1));
        cmd.push_back(line.substr(space + 1, line.npos));
        current_command = whisper;
    } else {
        current_command = message;
        cmd.push_back(line);
        found = true;
    }
    if (!found)
        throw CommandErrorException();
}

void CommandHandler::cmd_whisper(ClientId client_id, position_t target,
                                 SlotId slot) {
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
                   " esta desconectado o no existe.";
        server_manager.send_to(client_id, EventFactory::chat_message(chat_msg));
    }
}

void CommandHandler::cmd_message(ClientId client_id, position_t target,
                                 SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    Session& session = server_manager.get_session(client_id);
    std::string chat_msg = "[todos] " +
                           server_manager.get_name_by_client(client_id) + ": " +
                           cmd[0];
    session.broadcast(EventFactory::chat_message(chat_msg));
}

void CommandHandler::cmd_help(ClientId client_id, position_t target,
                              SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    std::string msg;
    if (cmd.size() == 1) {
        msg = "[info] Mantenga presionado F1 para ver los controles.\n" +
              message.help + "\n" + whisper.help + "\n" +
              "[info] Los comandos existentes son: ";
        size_t i = 36;
        for (auto it = commands.begin(); it != commands.end(); it++) {
            const command_case_t& command = *it;
            i += (command.cmd.length() + 1);
            msg += command.cmd.substr(1, command.cmd.npos);
            if (i < 80 && it != --(commands.end()))
                msg += ", ";
            else {
                msg += "\n";
                i = 0;
            }
        }
    } else {
        auto it = commands.begin();
        while (it->cmd.substr(1, std::string::npos) != cmd[1]) {
            it++;
            if (it == commands.end())
                throw CommandErrorException();
        }
        msg = "[" + it->cmd + "] " + it->help;
    }
    server_manager.send_to(client_id, EventFactory::chat_message(msg));
}

void CommandHandler::cmd_disconnect(ClientId client_id, position_t target,
                                    SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.send_to(client_id, EventFactory::disconnect());
    server_manager.drop_client(client_id);
}

void CommandHandler::cmd_pickup(ClientId client_id, position_t target,
                                SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::pickup_event(client_id));
}

void CommandHandler::cmd_drop(ClientId client_id, position_t target,
                              SlotId slot) {
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

void CommandHandler::cmd_resuscitate(ClientId client_id, position_t target,
                                     SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::resuscitate_event(client_id));
}

void CommandHandler::cmd_heal(ClientId client_id, position_t target,
                              SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::heal_event(client_id, target));
}

void CommandHandler::cmd_list(ClientId client_id, position_t target,
                              SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::list_event(client_id, target));
}

void CommandHandler::cmd_buy(ClientId client_id, position_t target,
                             SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = 1;
    slot = 0;
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
    server_manager.dispatch(
        EventFactory::buy_event(client_id, target, (SlotId)slot, amount));
}

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

void CommandHandler::cmd_deposit_item(ClientId client_id, position_t target,
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
        EventFactory::deposit_item_event(client_id, target, slot, amount));
}

void CommandHandler::cmd_withdraw_item(ClientId client_id, position_t target,
                                       SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = 1;
    slot = 0;
    try {
        slot = std::stoul(cmd[1]);
        if (amount > std::numeric_limits<SlotId>::max())
            throw CommandErrorException();
        if (cmd.size() == 3)
            amount = std::stoul(cmd[2]);
    } catch (const std::invalid_argument& e) {
        throw CommandErrorException();
    } catch (const std::out_of_range& e) {
        amount = UINT32_MAX;
    }
    server_manager.dispatch(
        EventFactory::withdraw_item_event(client_id, target, slot, amount));
}

void CommandHandler::cmd_withdraw_gold(ClientId client_id, position_t target,
                                       SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = UINT32_MAX;
    try {
        if (cmd.size() == 2)
            amount = std::stoul(cmd[1]);
    } catch (const std::invalid_argument& e) {
        throw CommandErrorException();
    } catch (const std::out_of_range& e) {
        amount = UINT32_MAX;
    }
    server_manager.dispatch(
        EventFactory::withdraw_gold_event(client_id, target, amount));
}

void CommandHandler::cmd_deposit_gold(ClientId client_id, position_t target,
                                      SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    uint32_t amount = UINT32_MAX;
    try {
        if (cmd.size() == 2)
            amount = std::stoul(cmd[1]);
    } catch (const std::invalid_argument& e) {
        throw CommandErrorException();
    } catch (const std::out_of_range& e) {
        amount = UINT32_MAX;
    }
    server_manager.dispatch(
        EventFactory::deposit_gold_event(client_id, target, amount));
}

void CommandHandler::cmd_meditate(ClientId client_id, position_t target,
                                  SlotId slot) {
    ServerManager& server_manager = ServerManager::get_instance();
    server_manager.dispatch(EventFactory::meditate_event(client_id));
}

void CommandHandler::handle(Event& event) {
    nlohmann::json json = event.get_json();
    try {
        std::string msg = json["msg"];
        parse_line(msg);
        (this->*current_command.handle)(json["client_id"], json["target"],
                                        json["slot"]);
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

CommandHandler::CommandHandler()
    : BlockingThEventHandler(), space(0), current_command(message) {
    std::cerr << "CommandHandler: starting.." << std::endl;
}
CommandHandler::~CommandHandler() {}
