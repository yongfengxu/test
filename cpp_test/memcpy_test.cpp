#include <iostream>
#include <memory.h>
using namespace std;

int main()
{
    char src[] = "hello";
    char dest[] = "world";

    cout << dest << endl;
    memcpy(dest, src + 1, 4);
    cout << dest << endl;
}
