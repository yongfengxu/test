#ifndef _COLLEAGE_H_
#define _COLLEAGE_H_

#include <string>

using namespace std;

class Mediator;
class Colleage
{
public:
	virtual ~Colleage();
	virtual void Action() = 0;
	virtual void SetState(const string& str) = 0;
	virtual string GetState() = 0;

protected:
	Colleage();
	Colleage(Mediator* mdt);
	Mediator* _mdt;
};

class ConcreteColleageA:public Colleage
{
public:
	ConcreteColleageA();
	ConcreteColleageA(Mediator* mdt);
	~ConcreteColleageA();
	virtual void Action();
	virtual void SetState(const string& str);
	virtual string GetState();

private:
	string _str;
};

class ConcreteColleageB:public Colleage
{
public:
	ConcreteColleageB();
	ConcreteColleageB(Mediator* mdt);
	~ConcreteColleageB();
	virtual void Action();
	virtual void SetState(const string& str);
	virtual string GetState();

private:
	string _str;
};

#endif
