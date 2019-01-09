#include <iostream>


class B { // BAD: polymorphic base class doesn't suppress copying
public:
    //B(const B& b) = delete;
//    B& operator=(const B& b) = delete;

    virtual char m() { return 'B'; }
    // ... nothing about copy operations, so uses default ...
};

class D : public B {
public:
    char m() override { return 'D'; }
    // ...
};

void f(B& b) {
    auto b2 = b; // oops, slices the object; b2.m() will return 'B'
    std::cout << "b2.m() = " << b2.m() << std::endl;
}

int main()
{
    D d;
    f(d);

    std::cout << "d.m() = " << d.m() << std::endl;
}
