#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include "ICar.h"
#include "IBuilder.h"

class Director
{
public:
    Director();
    ~Director();
    ICar* getBMW();
    ICar* getAudi();

private:
    IBuilder* bmwBuilder_;
    IBuilder* audiBuilder_;
};

#endif
