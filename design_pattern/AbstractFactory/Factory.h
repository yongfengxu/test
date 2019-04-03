#ifndef FACTORY_H_
#define FACTORY_H_
#include "IProduct.h"
#include "IAbstractFactory.h"

class Factory1 : public IAbstractFactory
{
public:
    IProductA* createProductA() override;
    IProductB* createProductB() override;

};

class Factory2 : public IAbstractFactory
{
public:
    IProductA* createProductA() override;
    IProductB* createProductB() override;

};

#endif
