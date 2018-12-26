#include <iostream>

using namespace std;

union sc
{
    short s;
    char c[2];
};

int main()
{
    if (sizeof(short) == 2)
    {
        sc sc;
        sc.s = 0x0102;
        if (sc.c[0] == 0x02 && sc.c[1] == 0x01)
        {
            cout << "little endian" << endl;
        }
        else if (sc.c[0] == 0x01 && sc.c[1] == 0x02)
        {
            cout << "big endian" << endl;
        }
        else
        {
            cout << "unknown" << endl;
        }
    }
    else
    {
        cout << "sizeof(short) is " << sizeof(short) << endl;
    }
}
