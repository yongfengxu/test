#ifndef CLIENT_H
#define CLIENT_H

#include "ITestTx.h"
#include "ITestRx.h"

#include <iostream>

class Client:public ITestTx
{
public:
	explicit Client(ITestRx& rx):itsTestRx(rx) {}
	ITestRx& getRx() {return itsTestRx;}
private:
	virtual void onStartRsp(int value) {std::cout << "Client::onStartRsp value = " << value  << std::endl;}
	ITestRx& itsTestRx;

};

#endif
