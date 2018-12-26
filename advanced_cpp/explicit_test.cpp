#include <iostream>
using namespace std;

class A
{
public:
	A()=default;
	explicit A(int i):a(i) {cout << "int a = " << a << endl;}
	A(short i):a(i) {cout << "short a = " << a << endl;}
	A& operator=(A &r) {cout << "oper=\n";}
	~A() {}

	operator int() const { cout << "int()" << endl; return static_cast<int> (a);}
	operator short() const {cout << "short()" << endl; return static_cast<short> (a);}
private:
	int a=1;
};

int main()
{
    	A objA = static_cast<A> (10);	

	short a = objA;

	cout << a << endl;
	
	return 0;
}
