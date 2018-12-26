#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h"
#include <iostream>
#include <list>

using namespace std;

class IObserver;

class ISubject
{
public:
	virtual ~ISubject() {}
	virtual void Attach(IObserver*) = 0;
	virtual void Detach(IObserver*) = 0;
	virtual void Notify() = 0;

	virtual void SetState(int) = 0;
	virtual int GetState() = 0;

protected:
	list<IObserver*> m_OberserList;
};


#endif
