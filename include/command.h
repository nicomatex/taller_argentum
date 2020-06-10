#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>

class Command {
   private:
   public:
    std::string str;

    Command() {}
    Command(std::string str) : str(str) {}

    void execute(std::ostream& out) {
        out << str;
    }

    ~Command() {}
};

#endif  // COMMAND_H
