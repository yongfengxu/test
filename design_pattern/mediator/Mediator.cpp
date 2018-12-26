#include "Mediator.h"
#include "Colleage.h"

Mediator::Mediator() {}

Mediator::~Mediator() {}

ConcreteMediator::ConcreteMediator() {}

ConcreteMediator::~ConcreteMediator() {}

ConcreteMediator::ConcreteMediator(Colleage* clgA, Colleage* clgB)
{
	_clgA = clgA;
	_clgB = clgB;
}


void ConcreteMediator::SetConcreteColleageA(Colleage* clgA)
{
	_clgA = clgA;
}

void ConcreteMediator::SetConcreteColleageB(Colleage* clgB)
{
	_clgB = clgB;
}

Colleage* ConcreteMediator::GetConcreteColleageA()
{
	return _clgA;
}

Colleage* ConcreteMediator::GetConcreteColleageB()
{
	return _clgB;
}


void ConcreteMediator::IntroColleage(Colleage* clgA, Colleage* clgB)
{
	_clgA = clgA;
	_clgB = clgB;
}

void ConcreteMediator::DoActionFromAtoB()
{
	_clgB->SetState(_clgA->GetState());
}

void ConcreteMediator::DoActionFromBtoA()
{
	_clgA->SetState(_clgB->GetState());
}

