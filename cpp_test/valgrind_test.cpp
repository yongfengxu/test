#include <iostream>
#include <map>

using namespace std;


int main()
{

    map<int, int> itsMap;

    map<int, int>::const_iterator iter;

    for (iter = itsMap.begin(); iter != itsMap.end(); ++iter)
    {
        cout << iter->first << " " << iter->second << endl;
    }
}

