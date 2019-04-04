#include "Car.h"


int main()
{
    BMW* car1 = new BMW();

    Audi* car2 = new Audi();

    car1->run();

    car2->setAlarm(false);
    car2->run();

    car2->setAlarm(true);
    car2->run();
}
