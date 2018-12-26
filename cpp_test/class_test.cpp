#include <iostream>

using namespace std;


class A {
private:
	char c;
};

class B:public A 
{
	int a;
};


int main()
{
	cout << sizeof(A) << " " << sizeof(B) << endl;

}
