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

    int a[11];

    std::cout << "sizeof a is " << getArrayLen(a) << std::endl;
}
