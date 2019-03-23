#include <iostream>
#include <list>

class ConcreteElementA;
class ConcreteElementB;

class IVisitor
{
public:
    ~IVisitor() = default;
    virtual void visitConcreteElementA(ConcreteElementA& element) = 0;
    virtual void visitConcreteElementB(ConcreteElementB& element) = 0;
};


class IElement
{
public:
    ~IElement() = default;
    virtual void doSomething() = 0;
    virtual void accept(IVisitor& visitor) = 0;
};

class ConcreteElementA : public IElement
{
public:
    void accept(IVisitor& visitor) {visitor.visitConcreteElementA(*this);}
    void doSomething() override {std::cout << "I'm A" << std::endl;}

};

class ConcreteElementB : public IElement
{
public:
    void accept(IVisitor& visitor) {visitor.visitConcreteElementB(*this);}
    void doSomething() override {std::cout << "I'm B" << std::endl;}

};

class ConcreteVisitor1 : public IVisitor
{
public:
    void visitConcreteElementA(ConcreteElementA& element) { print(); element.doSomething();}
    void visitConcreteElementB(ConcreteElementB& element) { print(); element.doSomething();}

    void print() {std::cout << "ConcreteVisitor1" << std::endl;}
};

class ConcreteVisitor2 : public IVisitor
{
public:
    void visitConcreteElementA(ConcreteElementA& element) { print(); element.doSomething();}
    void visitConcreteElementB(ConcreteElementB& element) { print(); element.doSomething();}
    void print() {std::cout << "ConcreteVisitor2" << std::endl;}
};

class ObjectStruct
{
public:
    void attach(IElement* e) {elements.push_back(e);}
    void detach(IElement* e) {elements.remove(e);}

    void accept(IVisitor* visitor) {for (auto e : elements) e->accept(*visitor);}

private:
    std::list<IElement*> elements;
};

int main()
{
    IElement* elementA = new ConcreteElementA();
    IElement* elementB = new ConcreteElementB();
    ObjectStruct* obs = new ObjectStruct();
    obs->attach(elementA);
    obs->attach(elementB);


    IVisitor* visitor1 = new ConcreteVisitor1();
    IVisitor* visitor2 = new ConcreteVisitor2();

    obs->accept(visitor1);
    obs->accept(visitor2);

}
