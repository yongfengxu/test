#include <iostream>
#include <vector>
#include <set>

using namespace std;

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
    cout << sizeof(a) << endl;
}
