#include <iostream>
#include <vector>
#include <cstdlib>

class Type
{
public:
    Type(int aa) : a(aa) {}

private:
    int a;
};


void fun(const Type& type)
{
    std::abort();
}

int main()
{
    Type type(1);
    fun(type);
}
