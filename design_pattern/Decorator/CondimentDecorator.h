#ifndef CONDIMENTDECORATOR_H_
#define CONDIMENTDECORATOR_H_
#include "IBeverage.h"

class CondimentDecorator: public IBeverage
{
public:
    CondimentDecorator(IBeverage* beverage):beverage_(beverage) {}

    virtual ~CondimentDecorator() = default;
    virtual std::string getDescription() = 0;

    IBeverage* beverage_;


};

#endif
