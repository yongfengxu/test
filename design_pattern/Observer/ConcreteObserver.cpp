#include "ConcreteObserver.h"
#include "IObservable.h"
#include <iostream>

ConcreteObserver::ConcreteObserver(std::string name, IObservable* observable):name_(name), observable_(observable)
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

void ConcreteObserver::activeDisplay(int state)
{
    std::cout << name_ << " pull it by myself, state is " << state << std::endl;
}

void ConcreteObserver::setObservable(IObservable* observable)
{
    observable_ = observable;
}

void ConcreteObserver::subscribe()
{
    if (observable_)
    {
        observable_->attach(this);
    }
}


void ConcreteObserver::unsubscribe()
{
    if (observable_)
    {
        observable_->detach(this);
    }
}

void ConcreteObserver::requestSomething()
{
    if (observable_)
    {
        observable_->pullSomething(*this);
    }
}

