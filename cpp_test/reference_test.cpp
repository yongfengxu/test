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
    fun(a);
}

