#include "Director.h"
#include "ICar.h"


int main()
{
    Director* d = new Director();

    ICar* bmw = d->getBMW();
    bmw->run();

    ICar* audi = d->getAudi();
    audi->run();

    delete d;
}
