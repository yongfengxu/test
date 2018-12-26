#include <iostream>
#include <assert.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace boost;

int main()
{
	shared_ptr<int> sp(new int(10));
	shared_ptr<int> sp1(new int(20));

	assert(sp.unique());

	shared_ptr<int> sp2 = sp;
	assert(sp == sp2 && sp.use_count() == 2);

	*sp2 = 100;
	assert(*sp == 100);

	sp2 = sp1;
	assert(!sp1.unique());

	cout << "sp use_count: " << sp.use_count() << endl;

	sp.reset();
	cout << "sp use_count: " << sp.use_count() << endl;
	cout << "sp1 use_count: " << sp1.use_count() << endl;
	cout << "sp2 use_count: " << sp2.use_count() << endl;
	assert(*sp2 == 20);

	//cout << "*sp = " << *sp << " *sp2 = " << *sp2 << endl;

}

