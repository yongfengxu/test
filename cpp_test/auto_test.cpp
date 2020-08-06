#include <iostream>

void test()
{
    int i = 0;
    int &r = i;

    const int ci = i;
    const int &cr = ci;

    auto a = r;
    auto b = ci;
    auto c = cr;
    auto d = &i;
    auto e = &ci;

    const auto f = ci;
    auto &g = ci;

    //auto &h = 42;
    const auto &j = 42;

    auto k = ci;
    auto &l = i;
    auto &m = ci;
    auto *p = &ci;
    auto &n = i;
    auto *p2 = &ci;

}

int main()
{
    const int i = 42;
    const int a = 442;

    //=======================================
    auto j = i; // type of j is int
    std::cout << "j = " << j << std::endl;
    j = 442;
    std::cout << "j = " << j << std::endl;

    //=======================================
    const auto &k = i; // type of k is const int&

    //=======================================
    auto *p = &i; // type of p is pointer

    std::cout << "*p = " << *p << std::endl;
    p = &a;
    std::cout << "*p = " << *p << std::endl;

    //=======================================
    const auto j2 = i; // type of j2  is const int

    //=======================================
    const auto &k2 = i; // type of k2 is const int&
}
