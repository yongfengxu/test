#ifndef CONCRETE_COMMAND2_H
#define CONCRETE_COMMAND2_H

#include "Command.h"
#include "Receiver.h"

class ConcreteCommand2: public Command
{
public:
    ConcreteCommand2(Receiver* receiver);
    void execute() override;

private:
    Receiver* receiver_;
};

#endif
