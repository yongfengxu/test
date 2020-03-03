#include <iostream>
#include <functional>
#include <cassert>

using std::placeholders::_1;

class ServiceManager
{
public:
    int get(int a) { return a; }
    void setCallback();

    void print();
private:
    std::function<int(int)> pf;
};

void ServiceManager::setCallback()
{
     pf = std::bind(&ServiceManager::get, this, _1);
}

void ServiceManager::print()
{
    try
    {
        int a = pf(10);
        std::cout << "hello " << a << std::endl;
    }
    catch (const std::bad_function_call& e)
    {
        std::cout << e.what() << std::endl;
    }
}

struct Foo {
    Foo(int num) : num_(num) {}
    int print_add(int i) const { std::cout << num_+i << '\n'; return num_+i; }
    int num_;
};

int print_num(int i)
{
    std::cout << i << '\n';
    return i;
}

struct PrintNum {
    int operator()(int i) const
    {
        std::cout << i << '\n';
        return i;
    }
};


int main()
{
    // store a free function
    std::function<int(int)> f_display = print_num;
    assert(-9 == f_display(-9));

    // store a lambda
    std::function<int()> f_display_42 = []() {return  print_num(42); };
    assert(42 == f_display_42());

    // store the result of a call to std::bind
    std::function<int()> f_display_31337 = std::bind(print_num, 31337);
    assert(31337 == f_display_31337());

    // store a call to a member function
    std::function<int(const Foo&, int)> f_add_display = &Foo::print_add;
    const Foo foo(314159);
    assert(314160 == f_add_display(foo, 1));
    assert(314160 ==  f_add_display(314159, 1));

    // store a call to a data member accessor
    std::function<int(Foo const&)> f_num = &Foo::num_;

    std::cout << "num_: " << f_num(foo) << '\n';

    const Foo foo1(2048);
    assert(2048 == f_num(foo1));

    // store a call to a member function and object
    using std::placeholders::_1;
    std::function<int(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
    assert(314161 == f_add_display2(2));

    // store a call to a member function and object ptr
    std::function<int(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
    assert(314162 == f_add_display3(3));

    // store a call to a function object
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);

    //ServiceManager test
    ServiceManager sm;
    sm.print();

    sm.setCallback();
    sm.print();
}
