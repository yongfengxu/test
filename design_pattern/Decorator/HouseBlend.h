#ifndef HOUSEBLEND_H_
#define HOUSEBLEND_H_

#include "IBeverage.h"

class HouseBlend : public IBeverage
{
public:
    HouseBlend();
    double cost() override;
    std::string getDescription() override;

private:
    std::string description_;
}; 



#endif
