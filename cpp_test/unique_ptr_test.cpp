#include <iostream>
#include <memory>

void my_destruction(int* b)
{
    std::cout << "hello " << *b   << "\n"; 
}

bool fun1(std::unique_ptr<int> p)
{
    std::cout << *p << std::endl;

    return true;
}


void fun2(std::unique_ptr<int>& p)
{
    std::cout << *p << std::endl;
}


int main()
{

//    std::unique_ptr<int> p = std::make_unique<int>(5);
    std::unique_ptr<int, decltype(&my_destruction)> p(new int(5), &my_destruction);

    //fun2(p);
    //std::cout << *p << std::endl;

    //fun1(std::move(p));
    //std::cout << *p << std::endl;
}
