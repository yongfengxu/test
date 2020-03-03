#include <iostream>
#include <map>

using namespace std;


class A
{
public:
    A(int i):v(i) { cout << "A()" << endl;}
    A(const A& a);
  ~A() {cout << "~A()" << endl;}

private:
	int v;

};

A::A(const A& a)
{
    cout << "Copy Construction" << endl;
    v = a.v;
}


void test_advance()
{
    std::map<int, int> emptyMap;
    auto t = emptyMap.begin();

    std::cout << "hello world" << std::endl;

    std::advance(t, 2);

    std::cout << "what's happening?" << std::endl;

    std::cout << t->first << " " << t->second << std::endl;

    std::cout << "we'are here" << std::endl;
}

void magic_constructor() {

  map<int, A> m1;

  m1.emplace(std::piecewise_construct, std::forward_as_tuple(1),
             std::forward_as_tuple(3));

  A a1(1);
  m1.emplace(2, a1);

  /*
  auto result = m1.emplace(4, a1);
  cout << result.second << endl;
  */

  cout << "hello" << endl;
  m1.erase(1);
  m1.erase(2);

  cout << "world" << endl;

  /*
  map<int, int> mm;
  mm[1] = 1;
  mm[2] = 2;

  int a = mm[3];
  cout << a << endl;
  */
}

int main()
{

  test_advance();

	return 0;

}
