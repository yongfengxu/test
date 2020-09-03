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
    vector<int> va = {1, 3, 5, 6, 8};
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


    int x[10], *p = x;

    cout << "sizeof(p) = " << sizeof p << endl;
    cout << "sizeof(*p) = " << sizeof *p << endl;


    vector<int> myVector(10);
    auto j = myVector.size();
    for (auto i = 0; i != myVector.size(); i++,j--)
        //for (auto i = 0; i != myVector.size(); ++i, --j)
    {
        myVector[i] = j;
    }

    cout << "===" << endl;
    for (const auto& v : myVector)
    {
        cout << v << endl;
    }

    cout << "===" << endl;

}
