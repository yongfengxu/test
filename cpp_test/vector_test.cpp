#include <iostream>
#include <vector>
using namespace std;

void fun(const vector<int>& v)
{
    for (auto a : v)
    {
        cout << a << endl;
    }
}

int main()
{
    vector<int> v {10, 11};

    for (auto a : v)
    {
        cout << a << endl;
    }


    fun(vector<int>{12, 13});


}
