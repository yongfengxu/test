#include "ConcreteCommand2.h"

ConcreteCommand2::ConcreteCommand2(Receiver* receiver): receiver_(receiver)
{

}


void ConcreteCommand2::execute()
{
    receiver_->Action2();
}
