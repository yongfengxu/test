#include <iostream>

using namespace std;

class A
{
public:
	A() = default;
	explicit A(int i):data(i)
	{
		cout << "normal constuctor1!" << endl;
		pi = &data;
	}

	A(const A &a)
	{
		data = a.data;
		cout << "copy constructor!" << endl;
		pi = &data;
	}

	A(A &&a)
	{
		cout << "move constructor!" << endl;
		pi = a.pi;
	
		a.pi = NULL;
		a.data = 0;
	}

	A operator+(const A &a)
	{
		A temp(data + a.data);
		cout << endl << "operator+ called! show temp!" << endl;

		temp.show();
		cout << endl;
		return temp;
	}

	void show() const
	{
		cout << "pi=" << pi << " data=" << data << endl;

	}

private:
	int data;
	int *pi;
};


int main()
{
	int i = 99;
	A a(10);
	a.show();

	A b(i);
	b.show();

	A c(b);
	c.show();

	A d(b+c);
	d.show();
}

