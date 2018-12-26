#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <string>

using namespace std;


class Product;

class Builder
{
public:
	virtual ~Builder();
	virtual void BuildPartA(const string& buildPara) = 0;
	virtual void BuildPartB(const string& buildPara) = 0;
	virtual void BuildPartC(const string& buildPara) = 0;

	virtual Product* GetProduct() = 0;

protected:
	Builder();
};

class ConcreteBuilder:public Builder
{
public:
	ConcreteBuilder();
	~ConcreteBuilder();
	virtual void BuildPartA(const string& buildPara);
	virtual void BuildPartB(const string& buildPara);
	virtual void BuildPartC(const string& buildPara);

	virtual Product* GetProduct();


};
#endif
