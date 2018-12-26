#include <iostream>

using namespace std;

bool fun()
{
	return 0x00800000 & 0x80F2BF; 
}

int main()
{

	if (fun())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

}
