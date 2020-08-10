#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <class T>
static uint32_t getArrayLen(const T& array)
{
    return (sizeof(array) / sizeof(array[0]));
}

int main()
{
    vector<int> va;
    set<int> sa;
    cout << sizeof(va) << endl;
    cout << sizeof(sa) << endl;

    vector<char> vaa;
    set<char> saa;
    cout << sizeof(vaa) << endl;
    cout << sizeof(saa) << endl;

    int a = 1;
    cout << "sizeof(int) = " << sizeof(a) << endl;

    uint8_t ua = 1;
    cout << "sizeof(uint8_t) = " << sizeof(ua) << endl;

    cout << "sizeof(long) = " << sizeof(long) << endl;
    cout << "sizeof(long long) = " << sizeof(long long) << endl;

}
