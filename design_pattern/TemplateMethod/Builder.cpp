#include "Builder.h"

void BMWBuilder::buildCar()
{
    delete car_;
    car_ = new BMW();
}

ICar* BMWBuilder::getCar()
{
    return car_;
}

void BMWBuilder::setSequenceNumber(unsigned num)
{
    car_->setSequenceNumber(num);
}

void AudiBuilder::buildCar()
{
    delete car_;
    car_ = new Audi();
}


ICar* AudiBuilder::getCar()
{
    return car_;
}

void AudiBuilder::setSequenceNumber(unsigned num)
{
    car_->setSequenceNumber(num);
}
