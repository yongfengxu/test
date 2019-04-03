#ifndef IPRODUCTB_H_
#define IPRODUCTB_H_

#include "IProduct.h"
#include <iostream>

class ProductB1 : public IProductB
{
public:
    void doSomething() override;
};

class ProductB2 : public IProductB
{
public:
    void doSomething() override;
};


#endif
