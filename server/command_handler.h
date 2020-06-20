#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <string>

#include "../include/event.h"
#include "th_event_handler.h"

enum cmd_type {
    CMD_MESSAGE,
    CMD_MEDITATE,
    CMD_RESUCITATE,
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
    CMD_HELP
};

class CommandHandler : public ThEventHandler {
   private:
    enum cmd_type cmd_type;
    std::vector<std::string> cmd;

    void parse_line(const std::string& cmd);

   protected:
    void run_handler() override;

   public:
    CommandHandler(Event ev);
    ~CommandHandler();
};

#endif  // COMMAND_HANDLER_H
