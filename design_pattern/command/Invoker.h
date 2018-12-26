#ifndef INVOKER_H
#define INVOKER_H

#include "Command.h"
#include <vector>

class Invoker
{
public:
    void setCommand(Command* command);

    void notify();

private:
    std::vector<Command*> vCommand;
};

#endif
