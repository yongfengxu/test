#include <iostream>

using namespace std;

void fun1(int* val1)
{
    cout << "val1 address " << val1 << endl;
}

void fun(int& val)
{
    cout << "val " << &val << endl;
    fun1(&val);
}

int main()
{
    int a = 10;
    cout << "a " << &a << endl;
    //fun(a);

    int i = 0, &r1 = i;
    double d = 0, &r2 = d;

    r2 = 3.1415; //ok
    r2 = r1;

    i = r2;
    r1 = d;

    i = 5, r1 = 100;

    std::cout << i << " " << r1 << std::endl;
}

