#include <iostream>

int main()
{
    unsigned char c = -1;
    std::cout << "c = " << static_cast<int>(c) << std::endl;

    c = -2;
    std::cout << "c = " << static_cast<int>(c) << std::endl;

    c = 256;
    std::cout << "c = " << static_cast<int>(c) << std::endl;

    char d = 258;
    std::cout << "d = " << static_cast<int>(d) << std::endl;

}
