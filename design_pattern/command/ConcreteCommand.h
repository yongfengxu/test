#ifndef CONCRETE_COMMAND_H
#define CONCRETE_COMMAND_H

#include "Command.h"
#include "Receiver.h"

class ConcreteCommand: public Command
{
public:
    ConcreteCommand(Receiver* receiver);
    void execute() override;

private:
    Receiver* receiver_;
};

#endif
