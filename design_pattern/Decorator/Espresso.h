#ifndef ESPRESSO_H_
#define ESPRESSO_H_

#include "IBeverage.h"

class Espresso: public IBeverage
{
public:
    Espresso();
    double cost() override;
    std::string getDescription() override;

private:
    std::string description_;
};

#endif
