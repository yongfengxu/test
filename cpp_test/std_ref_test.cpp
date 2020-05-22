#include <functional>
#include <iostream>
#include <cassert>

using std::placeholders::_1;

void f(int &n1, int &n2, const int &n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
        // ++n3; // compile error
}

int main()
{
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';

    bound_f();
    assert(n1 == 10);
    assert(n2 == 12);
    assert(n3 == 12);
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';

}
