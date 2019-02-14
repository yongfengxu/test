#ifndef IBEVERAGE_H_
#define IBEVERAGE_H_

#include <string>

class IBeverage
{
public:
    virtual ~IBeverage() = default;

    virtual std::string getDescription() = 0;

    virtual double cost() = 0;
};

#endif
