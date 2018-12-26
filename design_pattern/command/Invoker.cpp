#include "Invoker.h"
#include <vector>

void Invoker::setCommand(Command* command)
{
    vCommand.push_back(command);
}


void Invoker::notify()
{
    std::vector<Command*>::iterator iter;

    for (iter = vCommand.begin(); iter != vCommand.end(); ++iter)
    {
        (*iter)->execute();
    }
}
