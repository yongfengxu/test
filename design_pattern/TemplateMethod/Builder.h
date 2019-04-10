#ifndef BUILDER_H_
#define BUILDER_H_

#include "IBuilder.h"
#include "Car.h"

class BMWBuilder : public IBuilder
{
public:
    ~BMWBuilder() {delete car_;}
    void buildCar() override;
    void setSequenceNumber(unsigned num) override;
    ICar* getCar() override;

private:
    ICar* car_;
};

class AudiBuilder : public IBuilder
{
public:
    ~AudiBuilder() {delete car_;}

    void buildCar() override;
    void setSequenceNumber(unsigned num) override;
    ICar* getCar() override;
private:
    ICar* car_;
};

#endif
