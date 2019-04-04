#include "ICar.h"

void ICar::run()
{
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
