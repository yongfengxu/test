#include "ICar.h"
#include <iostream>

void ICar::run()
{
    std:: cout << "no." << num_ << " car!!" << std::endl;
    start();
    if (isAlarm())
    {
        ring();
    }
    go();
}

bool ICar::isAlarm()
{
    return true;
}
