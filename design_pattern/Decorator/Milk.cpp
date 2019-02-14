#include "Milk.h"


Milk::Milk(IBeverage* beverage): beverage_(beverage)
{
}

std::string Milk::getDescription()
{
    return beverage_->getDescription() + " Milk";
}

double Milk::cost()
{
    return beverage_->cost() + 0.2;
}
