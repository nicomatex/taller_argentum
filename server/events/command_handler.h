#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <functional>
#include <string>

#include "../../include/blocking_th_event_handler.h"
#include "../../include/event.h"
#include "../../include/types.h"
#include "../game/position.h"

class CommandHandler;

typedef struct command_case {
    std::string cmd;
    std::function<bool(const std::vector<std::string>&)> condition;
    std::string help;
    void (CommandHandler::*handle)(ClientId client_id, position_t target,
                                   SlotId slot);
} command_case_t;

class CommandHandler : public BlockingThEventHandler {
   private:
    static const command_case_t whisper;
    static const command_case_t message;
    static const std::vector<command_case_t> commands;
    size_t space;
    command_case_t current_command;
    std::vector<std::string> cmd;

    void parse_line(const std::string& cmd);

   protected:
    void handle(Event& ev) override;

   public:
    CommandHandler();
    ~CommandHandler();

    void cmd_whisper(ClientId client_id, position_t target, SlotId slot);

    void cmd_message(ClientId client_id, position_t target, SlotId slot);

    void cmd_help(ClientId client_id, position_t target, SlotId slot);

    void cmd_disconnect(ClientId client_id, position_t target, SlotId slot);

    void cmd_pickup(ClientId client_id, position_t target, SlotId slot);

    void cmd_drop(ClientId client_id, position_t target, SlotId slot);

    void cmd_resuscitate(ClientId client_id, position_t target, SlotId slot);

    void cmd_heal(ClientId client_id, position_t target, SlotId slot);

    void cmd_unequip_all(ClientId client_id, position_t target, SlotId slot);

    void cmd_list(ClientId client_id, position_t target, SlotId slot);

    void cmd_buy(ClientId client_id, position_t target, SlotId slot);

    void cmd_sell(ClientId client_id, position_t target, SlotId slot);

    void cmd_deposit_item(ClientId client_id, position_t target, SlotId slot);

    void cmd_withdraw_item(ClientId client_id, position_t target, SlotId slot);

    void cmd_deposit_gold(ClientId client_id, position_t target, SlotId slot);

    void cmd_withdraw_gold(ClientId client_id, position_t target, SlotId slot);

    void cmd_meditate(ClientId client_id, position_t target, SlotId slot);
};

#endif  // COMMAND_HANDLER_H
