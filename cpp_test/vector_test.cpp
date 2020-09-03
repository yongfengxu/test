#include <iostream>
#include <vector>
#include <cctype>
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

template<typename t>
void printv(const vector<t>& v)
{
    cout << "=====================" << endl;
    for (const auto& a : v)
    {
        cout << a << endl;
    }
    cout << "=====================" << endl;

    auto size = v.size();
    cout << "vector size is " << size << endl;
}

void fun()
{
    vector<string> v5 {"hi"};
    printv(v5);

    vector<string> v6(2, "nnnn");
    printv(v6);

    vector<string> v7{"hh", "bb"};
    printv(v7);

    vector<string> v8{10};
    printv(v8);

    vector<vector<int>> a;

}

void fun1()
{
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

void read_print_int()
{
    vector<int> va;
    int i = 0;
    while (cin >> i)
        va.emplace_back(i);

    printv(va);
}

void convert_upper(string& str)
{
    for (auto& s : str)
    {
        s = toupper(s);
    }
}

void read_print_string()
{
    vector<string> vs;
    string s;
    while (cin >> s)
    {
        convert_upper(s);
        vs.emplace_back(s);
    }
    printv(vs);

}

int main()
{
    vector<int> a(1);
    cout << a[1];

    read_print_string();
}
