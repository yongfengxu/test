#include <iostream>

int main()
{
    int* a = new int(100);
    int* b = a;

    a = nullptr;

    delete a;

    std::cout << *b << std::endl;

    delete b;
}


