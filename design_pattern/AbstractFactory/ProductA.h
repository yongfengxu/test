#ifndef IPRODUCTA_H_
#define IPRODUCTA_H_

#include "IProduct.h"

class ProductA1 : public IProductA
{
public:
    void doSomething() override;
};


class ProductA2 : public IProductA
{
public:
    void doSomething() override;
};

#endif
