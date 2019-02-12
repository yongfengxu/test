#include "ConcreteObserver.h"
#include "ISubject.h"
#include <iostream>

ConcreteObserver::ConcreteObserver(std::string name, ISubject* subject):name_(name), subject_(subject)
{
    //subscribe();
}


ConcreteObserver::~ConcreteObserver()
{
    //unsubscribe();
}

void ConcreteObserver::display(int state)
{
    std::cout << name_ << "'s state is " << state << std::endl;
}

void ConcreteObserver::setSubject(ISubject* subject)
{
}

void ConcreteObserver::subscribe()
{
    if (subject_)
    {
        subject_->attach(this);
    }
}


void ConcreteObserver::unsubscribe()
{
    if (subject_)
    {
        subject_->detach(this);
    }
}
