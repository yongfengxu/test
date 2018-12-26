#ifndef CONCRETESUBJECT_H
#define CONCRETESUBJECT_H

#include "ISubject.h"
#include <iostream>

class ConcreteSubject:public ISubject
{
public:
	virtual void Attach(IObserver* observer);
	virtual void Detach(IObserver* observer);
	virtual void Notify();

	void SetState(int);
	int GetState();

private:
	int _state;
};

#endif
