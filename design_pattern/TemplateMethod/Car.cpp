#include "Car.h"

#include <iostream>

void BMW::start()
{
    std::cout << "BMW start" << std::endl;
}

void BMW::ring()
{
    std::cout << "BMW ring" << std::endl;
}

void BMW::go()
{
    std::cout << "BMW go" << std::endl;
}

bool BMW::isAlarm()
{
    return true;
}


void Audi::start()
{
    std::cout << "Audi start" << std::endl;
}

void Audi::ring()
{
    std::cout << "Audi ring" << std::endl;
}

void Audi::go()
{
    std::cout << "Audi go" << std::endl;
}


void Audi::setAlarm(bool alarm)
{
    isAlarm_ = alarm;
}
bool Audi::isAlarm()
{
    return isAlarm_;
}
