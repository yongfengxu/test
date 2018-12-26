#include <iostream>
#include <map>
#include <cassert>

using namespace std;

int main()
{

	for (int i = 0; i < 1000; i++)
	{
		map<int, int> my_map;
		map<int, int>::iterator iter;

		iter = my_map.find(1);
		assert(iter == my_map.end());
	}



}
