#include <iostream>
#include <type_traits>

#define A true
//#define B true
#define B false

void fun(bool f1, bool f2)
{
    static_assert(!(A && B), "f1 and f2 can't be true at the same time");


    std::cout << "hello" << std::endl;

}


int main()
{

    fun(true, true);
}
