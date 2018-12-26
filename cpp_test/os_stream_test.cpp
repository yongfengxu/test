#include <iostream>
#include <ostream>
#include <set>

using namespace std;

int main()
{
	set<int> s1;
	s1.insert(2);
	s1.insert(3);
	s1.insert(4);


	for (set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
	{
		cout << *it << endl;

	}

}
