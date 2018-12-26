#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

void fun()
{
	int *p = new int[4]{2, 4, 6, 7};

	for (int i = 0; i < 4; ++i)
	{
		cout << p[i] << endl;
	}

}

int sum(initializer_list<int> lst)
{
	int total = 0;
	for (const auto& value:lst)
		total += value;

	return total;
}

int main()
{

	int a = sum({1, 2, 3});
	int b = sum({10, 20, 30, 40});
	int c = sum({1, 2, 3.0});

}
