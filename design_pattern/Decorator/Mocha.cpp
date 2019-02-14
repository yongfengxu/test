#include "Mocha.h"


//Mocha::Mocha(IBeverage* beverage): beverage_(beverage)

Mocha::Mocha(IBeverage* beverage):CondimentDecorator(beverage)
{
}

std::string Mocha::getDescription()
{
    return beverage_->getDescription() + " Mocha";
}

double Mocha::cost()
{
    return beverage_->cost() + 0.2;
}
