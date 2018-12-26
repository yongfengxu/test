#include <iostream>

using namespace std;

auto printStr = []{cout << "This is a basic lambda" << endl;};

auto printValue = [](int val) mutable
{ 
	val += 1; 
	cout << "value = " << val << endl;
};

int main()
{
	int val = 11;
	auto captureVar = [val]() mutable {val += 1; cout << "val " << val << endl;};
//	printStr();
	
//	printValue(val);

	captureVar();

	cout << val << endl;
}
