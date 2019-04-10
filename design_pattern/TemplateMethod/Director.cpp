#include "Director.h"
#include "Builder.h"

Director::Director()
{
    bmwBuilder_ = new BMWBuilder();
    audiBuilder_ = new AudiBuilder();
}

Director::~Director()
{
    delete bmwBuilder_;
    delete audiBuilder_;
}


ICar* Director::getBMW()
{
    bmwBuilder_->buildCar();
    bmwBuilder_->setSequenceNumber(11);
    return bmwBuilder_->getCar();
}


ICar* Director::getAudi()
{
    audiBuilder_->buildCar();
    audiBuilder_->setSequenceNumber(19);
    return audiBuilder_->getCar();
}

