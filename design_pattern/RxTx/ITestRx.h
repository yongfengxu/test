#ifndef ITESTRX_H
#define ITESTRX_H


#include "ITestTx.h"

class ITestRx
{
public:
	virtual void startReq(int v) = 0;

	virtual void setTx(ITestTx& testTx) = 0;

};

#endif
