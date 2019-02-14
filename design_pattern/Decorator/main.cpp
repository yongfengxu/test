#include <iostream>
#include <memory>
#include "Espresso.h"
#include "HouseBlend.h"
#include "Milk.h"
#include "Mocha.h"


int main()
{
    std::unique_ptr<IBeverage> espresso = std::make_unique<Espresso>();

    std::cout << "espresso " << espresso->cost() << std::endl;

    std::unique_ptr<IBeverage> milk = std::make_unique<Milk>(espresso.get());
    std::cout << milk->getDescription() << " "<< milk->cost() << std::endl;

    std::unique_ptr<IBeverage> mocha = std::make_unique<Mocha>(milk.get());

    std::cout << mocha->getDescription() << " "<< mocha->cost() << std::endl;

    std::unique_ptr<IBeverage> mocha2 = std::make_unique<Mocha>(espresso.get());

    std::cout << mocha2->getDescription() << " "<< mocha2->cost() << std::endl;
}

