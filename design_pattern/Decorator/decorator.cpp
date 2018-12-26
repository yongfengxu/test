#include <iostream>
#include <string>

using namespace std;

class Component
{
public:
    virtual void Operation() = 0;
};

class ConcreteComponent : public Component
{
public:
    void Operation() override
    {
        cout << "Concrete Component Operation" << endl;
    }
};

class Decorator : public Component
{
public:
    void SetComponent(Component* component)
    {
        this->component = component;
    }

    void Operation() override
    {
        if (component != NULL)
        {
            component->Operation();
        }

    }
protected:
    Component* component;
};

class ConcreteDecoratorA: public Decorator
{
public:
    void Operation() override
    {
        Decorator::Operation();
        addedState = "New State";
        cout << "Concrete Decorator A Operation" << endl;
    }
private:
    string addedState;
};

class ConcreteDecoratorB : public Decorator
{
public:
    void Operation() override
    {
        Decorator::Operation();
        AddedBehavior();
        cout << "Concrete Decorator B Operation" << endl;
    }

    void AddedBehavior()
    {
        cout << "Concrete Decorator B added behavior" << endl;
    }
};

class ConcreteDecoratorC : public Decorator
{
public:
    void Operation() override
    {
        Decorator::Operation();
        AddedBehavior();
        cout << "Concrete Decorator C Operation" << endl;
    }

    void AddedBehavior()
    {
        cout << "Concrete Decorator C added behavior" << endl;
    }
};

int main()
{
    ConcreteComponent* c = new ConcreteComponent();
    ConcreteDecoratorA* d1 = new ConcreteDecoratorA();
    ConcreteDecoratorB* d2 = new ConcreteDecoratorB();
    ConcreteDecoratorC* d3 = new ConcreteDecoratorC();

    d1->SetComponent(c);
//    d1->Operation();
    d2->SetComponent(d1);
    d3->SetComponent(d2);
    d3->Operation();

}

