#include <iostream>

using namespace std;

class A
{
public:
	//virtual ~A() {cout << "~A()" << endl;}
	~A() {cout << "~A()" << endl;}
};

class B:public A
{
public:
	~B() {cout << "~B()" << endl;}

};

int main()
{
	A* a = new B();
	delete a;

}
