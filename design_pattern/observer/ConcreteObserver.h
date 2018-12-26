#include "IObserver.h"

class ConcreteObserver:public IObserver
{
public:
	ConcreteObserver(ISubject* subject):_SubjectStates(0),_subject(subject) {_subject->Attach(this);}

	~ConcreteObserver() {_subject->Detach(this);}
	virtual void Update(ISubject*);

	void Show();
private:
	int _SubjectStates;
	ISubject* _subject;
};
