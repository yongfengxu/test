#include <iostream>

int main()
{
    unsigned u = 10, u2 = 42;
    std::cout << u2 - u << std::endl;   // 32
    std::cout << u - u2 << std::endl;   // 4294967264

    int i = 10, i2 = 42;
    std::cout << i2 - i << std::endl;   // 32
    std::cout << i - i2 << std::endl;   // -32
    std::cout << i - u << std::endl;    // 0
    std::cout << u - i << std::endl;    // 0

    u = 42;
    i = 10;
    std::cout << i - u << std::endl;    // 4294967264 == 2^32 - 32
    std::cout << u - i << std::endl;    // 32

    u = 10;
    i = -42;
    std::cout << i + i << std::endl;  // prints -84
    std::cout << u + i << std::endl;  // if 32-bit ints, prints 4294967264

}
