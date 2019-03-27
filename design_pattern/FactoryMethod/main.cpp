#include <iostream>

class IOperation
{
public:
    IOperation() : numberA(0), numberB(0) {}
    virtual ~IOperation() = default;
    virtual double getResult() = 0;

    double numberA;
    double numberB;
};

class AddOperation : public IOperation
{
public:
    double getResult() override {return numberA + numberB;}
};

class DelOperation : public IOperation
{
public:
    double getResult() override {return numberA - numberB;}
};

class IFactory
{
public:
    virtual ~IFactory() = default;
    virtual IOperation* createOperation() = 0;
};

class AddFactory : public IFactory
{
public:
    IOperation* createOperation() override {return new AddOperation();}
};

class DelFactory : public IFactory
{
 public:
    IOperation* createOperation() override {return new DelOperation();}
};

int main()
{
    IFactory* factory = new AddFactory();
    IOperation* operation = factory->createOperation();

    operation->numberA = 2;
    operation->numberB = 1;

    std::cout << operation->getResult() << std::endl;

    delete factory;
    delete operation;



    factory = new DelFactory();
    operation = factory->createOperation();

    operation->numberA = 2;
    operation->numberB = 1;

    std::cout << operation->getResult() << std::endl;

    delete factory;
    delete operation;

}


