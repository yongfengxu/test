#include "ConcreteSubject.h"
#include "ConcreteObserver.h"

#include <iostream>
#include <memory>
using namespace std;

int main()
{
	auto_ptr<ConcreteSubject> subject(new ConcreteSubject());
	auto_ptr<ConcreteObserver> ob1(new ConcreteObserver(subject.get()));
	auto_ptr<ConcreteObserver> ob2(new ConcreteObserver(subject.get()));

/*
	ConcreteSubject* subject = new ConcreteSubject();
	ConcreteObserver* ob1 = new ConcreteObserver(subject.get());
	ConcreteObserver* ob2 = new ConcreteObserver(subject.get());
*/

	subject->SetState(1);
	subject->Notify();
	ob1->Show();
	ob2->Show();

	cout << "subject state changed to 2" << endl;
	
	subject->SetState(2);
	subject->Notify();
	ob1->Show();
	ob2->Show();


	cout << "subject state changed to 3, and ob2 detach" << endl;

	subject->Detach(ob2.get());
	subject->SetState(3);

	subject->Notify();

	ob1->Show();
	ob2->Show();

//	delete ob1;
//	delete ob2;
//	delete subject;
}
