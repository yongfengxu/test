#ifndef IBUILDER_H_
#define IBUILDER_H_

#include "ICar.h"

class IBuilder
{
public:
    virtual ~IBuilder() = default;

    virtual void buildCar() = 0;
    virtual void setSequenceNumber(unsigned num) = 0;
    virtual ICar* getCar() =0;
};

#endif
