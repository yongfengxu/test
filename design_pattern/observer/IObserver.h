#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <iostream>
#include "ISubject.h"

class ISubject;

class IObserver
{
public:
	virtual ~IObserver() {}
	virtual void Update(ISubject*) = 0;
};



#endif
