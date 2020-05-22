#include <iostream>
#include <map>

using namespace std;

struct Base {
    Base() {std::cout << "Base()" << std::endl;}
    virtual void foo() = 0;
    virtual ~Base(){ std::cout << "~Base()" << std::endl;};
};

struct Derived : public Base {
  virtual void foo() override { cout << "Derived::foo()" << endl; }
};

class AAA
{
public:
    ~AAA()
    {
        std::cout << "~AAA()" << std::endl;
        ((Derived*)my_map[1])->~Derived();
    }

    void createMap()
    {
        Base* d1 = new Derived();
        Base* d2 = new Derived();
        Base* d3 = new Derived();

        my_map[1] = d1;
        my_map[2] = d2;
        my_map[3] = d3;
    }

    std::map<int, Base*> my_map;
};

void function()
{
  auto *pd = new Derived();
  //auto *pd = new (pool) Derived();
  Base *pb = pd;
  pd->~Derived();
  pb->foo();
}


int main()
{
    AAA* a = new AAA();
    a->createMap();

    Base* ad = a->my_map[1];

    delete a;

    ad->foo();

    //function();
}
