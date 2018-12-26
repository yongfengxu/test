#include <iostream>

using namespace std;


class Test
{
public:
    static const double PI;
    static const int num = 3.14;

    int a[num];

};

const double Test::PI = 3.14;
int main()
{

    Test test;
    cout << &test << endl;

    return 0;
}

