#include <iostream>
#include <set>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

using namespace std;

class Test
{
public:
	Test(string str):name(str) {cout << "Test() " << name << endl;}
	Test() {cout << "Test() " << endl;}
	~Test() {cout << "~Test() " << name << endl;}

	void print() const { cout << "name is " << name << endl; }
private:
	string name;
};

typedef boost::shared_ptr<Test> SharedTest;

void f_bad()
{
	Test *t = new Test("bad");
}

void unPack()
{
	cout << "unPack()" << endl;
}

void f_good()
{
	SharedTest test(new Test);

}

void test_scope1()
{
	cout << "=================f_bad()===================" << endl;
	f_bad();
	cout << "=================f_bad()===================" << endl;

	cout << "=================f_good()===================" << endl;
	f_good();
	cout << "=================f_good()===================" << endl;

}

typedef boost::shared_ptr<Test> testPtr;
typedef std::map<int, testPtr> testMap;
typedef std::set<int> ID;

testMap myMap;

void fun()
{
	ID ids;
	testPtr ptr(new Test("July"));
	ID::iterator it;
	for (int i = 0; i < 10; ++i)
	{
		ids.insert(i);
	}

	for (it = ids.begin(); it != ids.end(); ++it)
	{
		myMap[*it] = ptr;
	}	

	cout << "use count = " << ptr.use_count() << endl;
	ptr->print();

}

const testPtr getTestPtr(int value)
{
	testMap::iterator iter;
	iter = myMap.find(value);	

	if (iter != myMap.end())
	{
		cout << iter->first << endl;
		return iter->second;	
	}

	return testPtr();
}

int main()
{
	fun();

	testPtr ptr;
	ptr = getTestPtr(1);

	if (ptr == NULL)
	{
		cout << "shared ptr is NULL" << endl;
	}
	else
	{
		cout << "use count = " << ptr.use_count() << endl;
		ptr->print();
		testPtr p = ptr;
		cout << "use count = " << ptr.use_count() << endl;
	}
}
