#ifndef MILK_H_
#define MILK_H_

#include "CondimentDecorator.h"

class Milk : public CondimentDecorator
{
public:
    Milk(IBeverage* beverage);
    std::string getDescription() override;
    double cost() override;

private:
    IBeverage* beverage_;

};



#endif
