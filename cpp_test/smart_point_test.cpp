#include <iostream>
#include <string>
#include <memory>

using namespace std;

class CReport
{
public:
	CReport(const string s):str(s) {cout << "Constructor " << s << endl;}
	~CReport() {cout << "Destruction" << endl;}
	void comment(string owner) {cout << owner << " " << str << endl; }

private:
	string str;
};

class A {};
shared_ptr<A> fun()
{
	auto ptr = make_shared<A>();

	return ptr;
}

int main()
{
	unique_ptr<CReport> ps(new CReport((string)"Hello"));	
	ps->comment(string("ps"));

	unique_ptr<CReport> p1 = move(ps);
	p1->comment(string("p1"));

	shared_ptr<A> sharedPtr = fun();

}
