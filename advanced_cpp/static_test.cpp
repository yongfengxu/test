#include <iostream>

using namespace std;

class A
{
public:
	static void print() { cout << "hello" << endl;}

private:
	static int val;
};

int A::val = 10;


int main()
{
	A a;
	a.print();

	A::print();


}
