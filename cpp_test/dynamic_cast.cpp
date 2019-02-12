#include <iostream>
#include <memory>

class A
{
    virtual void f(){}
};

class B :  public A
{
    virtual void f(){}
};

class C :  public A { };
class D { virtual void f(){} };
class E : public B, public C { virtual void f(){} };




int main()
{
    E e;
    B &b = e;//upcast

    E& re = dynamic_cast<E&>(b);//downcast
    C&c = dynamic_cast<C&>(b);//sidecast


    try
    {
        D&d = dynamic_cast<D&>(e);
    }
    catch (std::bad_cast& bc)
    {//异常将被捕获
        std::cerr << "bad_cast caught: " << bc.what() << '\n';
    }

    system("pause");
    return 0;
}
