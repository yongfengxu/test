#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include "ICar.h"
#include "Builder.h"

class Director
{
public:
    ICar* getBMW();
    ICar* getAudi();

private:
    BMWBuilder bmwBuilder_;
    AudiBuilder audiBuilder_;
};

#endif
