#include <iostream>

using namespace std;

typedef unsigned char u8;

int main()
{
	int RestartCountOutOfOrderWindow = 128;

  bool t = true;
  bool f = false;
  cout << "static_cast<u8> (bool) " << static_cast<int> (static_cast<u8>(t)) << endl;
  cout << "static_cast<u8> (bool) " << static_cast<int> (static_cast<u8>(f)) << endl;


	
/*
	int m = static_cast<u8>(restartCnt - restartCnt_);
	cout << "static_cast<int>(restartCnt - restartCnt_)= " << m << endl;
	int i = static_cast<int>(restartCnt - restartCnt_) < RestartCountOutOfOrderWindow ? -1 : 1;
	cout << "i = " << i << endl;

	cout << static_cast<int>(static_cast<u8>(0-128)) << endl;

	int restartCnt_ = 0;
	int restartCnt = 0;

	do 
	{
		//cout << "please input restartCnt_:";
		//cin >> restartCnt_;

		cout << "please input restartCnt:";
		cin >> restartCnt;

		cout << "restartCnt = " << restartCnt << " restartCnt_ " << restartCnt_ << endl;

		int m = static_cast<u8>(restartCnt - restartCnt_);
		cout << "static_cast<int>(restartCn_ - restartCnt_)= " << m << endl;

		int i = static_cast<u8>(restartCnt_ - restartCnt) <= RestartCountOutOfOrderWindow ? -1 : 1;
		//cout << "i = " << i << endl;

		if (i == 1)
		{
			cout << "\n===valid restart counter, change restartCnt_ to " << restartCnt << " ===\n" << endl;	
			restartCnt_ = restartCnt;
		}
		else
		{
			cout << "\n===invalid restart counter===\n" << endl;	
		}
	}
	while (1);

*/
}
