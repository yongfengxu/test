#ifndef IABSTRACTFACTORY_H_
#define IABSTRACTFACTORY_H_

#include "IProduct.h"
class IAbstractFactory
{
public:
    ~IAbstractFactory() = default;
    virtual IProductA* createProductA() = 0;
    virtual IProductB* createProductB() = 0;

};

#endif
