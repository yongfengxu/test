#include "Factory.h"
#include "ProductA.h"
#include "ProductB.h"

IProductA* Factory1::createProductA()
{
    return static_cast<IProductA*>(new ProductA1());
}

IProductB* Factory1::createProductB()
{
    return new ProductB1();
}

IProductA* Factory2::createProductA()
{
    return new ProductA2();
}

IProductB* Factory2::createProductB()
{
    return new ProductB2();
}

