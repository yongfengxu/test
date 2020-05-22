#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
    A() { cout << this << " A()" << endl; }
    A(int a) { cout << this << " A(int) = " << a << endl; }
    ~A() { cout << this << " ~A()" << endl; }
    A(const A &a) { cout << this << " A(&) =" << a.v << endl; }

    int v;
};


class B
{
public:
    static A& getA() {return a;}

private:
    static A a;
};

A B::a(11);

void fun(const vector<int>& v)
{
    for (auto a : v)
    {
        cout << a << endl;
    }
}

int main()
{
    //A a;

    vector<A> vA;

    //vA.push_back(a);

    cout << "=====================" << endl;

    //A a = B::getA();

    cout << "=====================" << endl;
    vA.emplace_back(13);
    cout << "=====================" << endl;
    //vA.emplace_back(a);
    //vA.emplace_back(B::getA());
    vA.push_back(B::getA());
    cout << "=====================" << endl;
}
