#include <iostream>
#include "Command.h"
#include "Invoker.h"
#include "Receiver.h"
#include "ConcreteCommand.h"
#include "ConcreteCommand2.h"


int main()
{
    Invoker* invoker = new Invoker();
    Receiver* receiver = new Receiver();

    ConcreteCommand* cCommand1 = new ConcreteCommand(receiver);
    invoker->setCommand(cCommand1);

    ConcreteCommand2* cCommand2 = new ConcreteCommand2(receiver);
    invoker->setCommand(cCommand2);

    invoker->notify();


}
