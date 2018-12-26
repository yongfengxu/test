#include <iostream>

using namespace std;

class A
{
public:
	virtual void f(char ch) const { cout << ch << endl;}
	//virtual ~A() {cout << "~A()" << endl;}
	~A() {cout << "~A() no virtual" << endl;}
};

class B:public A
{
public:
	void f(char ch) const { cout << "B" << ch << endl;}
	~B() {cout << "~B()" << endl;}
};

class C:public B
{
public:
	void f(char ch) const {cout << "C " << ch << endl;}
};


int main()
{
	//A *p = new B();
	B *p = new B();

	//B *pb = new C();

	//pb->f('a');

	delete p;
	//delete pb;

}
