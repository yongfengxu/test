#include "Mediator.h"
#include "Colleage.h"
#include <iostream>

using namespace std;

Colleage::Colleage()
{

}

Colleage::Colleage(Mediator* mdt)
{
	_mdt = mdt;
}

Colleage::~Colleage()
{

}

ConcreteColleageA::ConcreteColleageA()
{

}

ConcreteColleageA::~ConcreteColleageA()
{

}

ConcreteColleageA::ConcreteColleageA(Mediator* mdt):Colleage(mdt)
{

}

string ConcreteColleageA::GetState()
{
	return _str;
}

void ConcreteColleageA::SetState(const string& str)
{
	_str = str;
}

void ConcreteColleageA::Action()
{
	_mdt->DoActionFromAtoB();
	cout << "State of ConcreteColleageB: " << this->GetState() << endl;
}


ConcreteColleageB::ConcreteColleageB()
{

}

ConcreteColleageB::~ConcreteColleageB()
{

}

ConcreteColleageB::ConcreteColleageB(Mediator* mdt):Colleage(mdt)
{

}

string ConcreteColleageB::GetState()
{
	return _str;
}

void ConcreteColleageB::SetState(const string& str)
{
	_str = str;
}

void ConcreteColleageB::Action()
{
	_mdt->DoActionFromBtoA();
	cout << "State of ConcreteColleageA: " << this->GetState() << endl;
}
