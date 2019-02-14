#include <iostream>
#include <memory>
#include "Espresso.h"
#include "HouseBlend.h"
#include "Milk.h"


int main()
{
    std::unique_ptr<IBeverage> espresso = std::make_unique<Espresso>();

    std::cout << "espresso " << espresso->cost() << std::endl;

    std::unique_ptr<IBeverage> milk = std::make_unique<Milk>(espresso.get());
    milk->getDescription();
    std::cout << "espresso + milk costs " << milk->cost() << std::endl;


}
