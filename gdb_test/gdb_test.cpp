#include <iostream>
#include <vector>
#include <cstdlib>

class Type
{
public:
    Type(int aa) : a(aa), b('a') {}

private:
    int a;
    char b;
};


void fun(const Type& type)
{
    std::abort();
}

int main()
{
    Type type(1324);
    fun(type);
}
