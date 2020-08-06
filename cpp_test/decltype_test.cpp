#include <iostream>

void test()
{
    int a = 3;
    int b = 4;
    decltype(a) c = a;
    decltype((b)) d = a;

    ++c;
    ++d;

    std::cout << "a = " << a << std::endl; // a = 4
    std::cout << "b = " << b << std::endl; // b = 4
    std::cout << "c = " << c << std::endl; // c = 4
    std::cout << "d = " << d << std::endl; // d = 4
}

void test1()
{
    int a = 3;
    int b = 4;

    decltype(a) c = a; // type of c is int

    std::cout << "c = " << c << std::endl;
    ++c;
    std::cout << "c = " << c << std::endl;
    std::cout << "a = " << a << std::endl;

    decltype(a = b) d = a; // type of d is int&

    std::cout << "d = " << d << std::endl; 
    d = 12;
    std::cout << "d = " << d << std::endl;
    std::cout << "a = " << a << std::endl;
}

void test2()
{
    const int a = 3;

    decltype(a) b = 4;
    const auto c = a;

    decltype((a)) d = a;
    auto &e = (a);
}

int main()
{
    test1();
}
