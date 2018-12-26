#include "ConcreteCommand.h"

ConcreteCommand::ConcreteCommand(Receiver* receiver): receiver_(receiver)
{

}


void ConcreteCommand::execute()
{
    receiver_->Action1();
}
