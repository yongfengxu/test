#include "Director.h"

ICar* Director::getBMW()
{
    bmwBuilder_.buildCar();
    bmwBuilder_.setSequenceNumber(11);
    return bmwBuilder_.getCar();
}


ICar* Director::getAudi()
{
    audiBuilder_.buildCar();
    audiBuilder_.setSequenceNumber(19);
    return audiBuilder_.getCar();
}

