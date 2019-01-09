#include <iostream>

using namespace std;

int main()
{
    int i = 0;
    int sum = 0;

    for (i = 0; i < 5000; ++i)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }

    }

}
