#ifndef MOCHA_H_
#define MOCHA_H_

#include "CondimentDecorator.h"

class Mocha : public CondimentDecorator
{
public:
    Mocha(IBeverage* beverage);
    std::string getDescription() override;
    double cost() override;
};



#endif
