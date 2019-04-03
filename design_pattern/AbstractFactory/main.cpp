#include "IAbstractFactory.h"
#include "IProduct.h"
#include "Factory.h"

int main()
{
    IAbstractFactory* factory1 = new Factory1();

    IProductA* a1 = factory1->createProductA();
    IProductB* b1 = factory1->createProductB();

    a1->doSomething();
    b1->doSomething();

    IAbstractFactory* factory2 = new Factory2();

    IProductA* a2 = factory2->createProductA();
    IProductB* b2 = factory2->createProductB();

    a2->doSomething();
    b2->doSomething();


}
