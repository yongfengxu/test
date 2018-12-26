#include <iostream>

using namespace std;


class Test
{
public:
    static const double PI = 3.14;
    static const int num = 3.14;

    int a[num];

};


int main()
{

    Test test;
    cout << &test << endl;

    return 0;
}

