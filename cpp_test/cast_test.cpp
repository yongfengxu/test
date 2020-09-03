#include <iostream>
#include <string>

int main()
{
    int i = 9;
    double d = 1.23;

    const std::string *ps;
    char *pc;
    void *pv;

    pv = (void*)ps;
    pv = reinterpret_cast<void*>(const_cast<std::string *>(ps));

    i = int(*pc);
    i = static_cast<int>(*pc);

    pv = &d;
    pv = static_cast<void*>(&d);

    pc = (char*)pv;

    pc = static_cast<char*>(pv);


    int j = 3.15 + 3;
}
