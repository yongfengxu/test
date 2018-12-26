#ifndef SERVER_H
#define SERVER_H

#include "ITestRx.h"
#include "ITestTx.h"

#include <iostream>

class Server:public ITestRx
{
public:
	Server():itsTestTx(0) {}
	virtual void startReq(int value) 
	{
		std::cout << "Server::startReq" << std::endl;
		s_value  = value;
	}

	virtual void setTx(ITestTx& tx) { itsTestTx = &tx; }
	ITestTx* getTx() {return itsTestTx;}
	void print() {std::cout << "value = " << s_value << std::endl; }
	int getValue() {return s_value;}
private:
	ITestTx* itsTestTx;
	int s_value;
};

#endif
