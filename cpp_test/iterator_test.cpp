#include <vector>
#include <iostream>

using namespace std;

int main()
{
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	std::vector<int> vec(a, a + 10);
	std::vector<int>::const_iterator iter = vec.begin();
	//iter++;

	const vector<int>::iterator iter1 = vec.begin();
	*iter1 = 20;

	for ( ; iter != vec.end(); ++iter)
	{
		cout << *iter << " ";
	}

	cout << endl;



	
}

