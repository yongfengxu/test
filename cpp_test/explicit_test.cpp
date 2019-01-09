#include <iostream>

class A
{
public:
	A()=default;
	explicit A(int i):a(i) {std::cout << "int a = " << a << std::endl;}
	A(short i):a(i) {std::cout << "short a = " << a << std::endl;}
	A& operator=(A &r) {std::cout << "oper=\n";}
	~A() {}

	operator int() const { std::cout << "int()" << std::endl; return static_cast<int> (a);}
	operator short() const {std::cout << "short()" << std::endl; return static_cast<short> (a);}
private:
	int a=1;
};

int main()
{
    	A objA = static_cast<A> (10);	

	short a = objA;

	std::cout << a << std::endl;       // 
	
	return 0;
}
