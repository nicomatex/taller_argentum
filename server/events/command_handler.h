#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>

#include "../../include/blocking_th_event_handler.h"
#include "../../include/event.h"
#include "../../include/types.h"
#include "../game/position.h"

enum cmd_type {
    CMD_MESSAGE,
    CMD_MEDITATE,
    CMD_RESUSCITATE,
    CMD_HEAL,
    CMD_DEPOSIT_ITEM,
    CMD_DEPOSIT_GOLD,
    CMD_WITHDRAW,
    CMD_LIST,
    CMD_BUY,
    CMD_SELL,
    CMD_PICKUP,
    CMD_DROP,
    CMD_WHISPER,
    CMD_DISCONNECT,
    CMD_UNEQUIP,
    CMD_HELP
};

class CommandHandler : public BlockingThEventHandler {
   private:
    size_t space;
    enum cmd_type cmd_type;
    std::vector<std::string> cmd;

    void parse_line(const std::string& cmd);

    void cmd_whisper(ClientId client_id);

    void cmd_message(ClientId client_id);

    void cmd_help(ClientId client_id);

    void cmd_disconnect(ClientId client_id);

    void cmd_pickup(ClientId client_id);

    void cmd_drop(ClientId client_id, SlotId slot);

    void cmd_resuscitate(ClientId client_id, position_t target);

    void cmd_unequip_all(ClientId client_id);

   protected:
    void handle(Event& ev) override;

   public:
    CommandHandler();
    ~CommandHandler();
};

#endif  // COMMAND_HANDLER_H
