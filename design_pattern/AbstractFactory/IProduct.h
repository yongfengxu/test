#ifndef IPRODUCT_H_
#define IPRODUCT_H_

class IProductA
{
public:
    ~IProductA() = default;
    virtual void doSomething() = 0;
};

class IProductB
{
public:
    ~IProductB() = default;
    virtual void doSomething() = 0;
};



#endif
