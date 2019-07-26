#include <iostream>
#include <map>

using namespace std;


class A
{
public:
	A(int i, int j):a(i), b(j) {}
	int a;

	int b;

};


int main()
{
	map<int, A> m1;

	A a1(1, 2);
	A a2(3, 4);

	m1.insert(make_pair(1, a1));
	m1.insert(make_pair(2, a2));


  /*
  auto result = m1.emplace(4, a1);
  cout << result.second << endl;
  */

  m1.erase(55);


  map<int, int> mm;
  mm[1] = 1;
  mm[2] = 2;

  int a = mm[3];
  cout << a << endl;

	return 0;

}
