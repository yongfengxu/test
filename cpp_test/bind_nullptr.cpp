#include <iostream>

using namespace std;


void fun(int& a)
{
    std::cout << a << std::endl;
}

int main()
{
    int* a = nullptr;

    fun(*a);




}
