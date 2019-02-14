#include "Espresso.h"

Espresso::Espresso() : description_("Espresso")
{
}

double Espresso::cost()
{
    return 1.99;
}

std::string Espresso::getDescription()
{
    return description_;
}
