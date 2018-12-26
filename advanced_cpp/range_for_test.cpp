#include <iostream>
#include <set>
#include <vector>

using namespace std;
typedef unsigned short u16;

int main()
{
	set<u16> result = {1, 2, 3, 4, 5};

	vector<u16> s(65530, 65535);
	for (const auto i : s)
		cout << i << endl;

	for (const u16& i : s)
		result.insert(i);

	for (const auto i : result)
		cout << i << endl;

}

