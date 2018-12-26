#include "ConcreteObserver.h"

#include <iostream>
using namespace std;

void ConcreteObserver::Update(ISubject* subject)
{
	_SubjectStates = subject->GetState();;
}

void ConcreteObserver::Show()
{
	cout << "my state is " << _SubjectStates<< endl;
}
