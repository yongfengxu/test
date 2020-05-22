#include <iostream>

using namespace std;


class A {

protected:
    void show() {cout << "hello" << endl;}

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

  A a;

  a.show();

}
