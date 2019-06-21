#include <iostream>

using namespace std;

class A
{
public:
    A() = default;
    ~A()
    {
        cout << "destructor" << endl;
    }

    explicit A(int i):data(i)
    {
        cout << "normal constuctor!" << endl;
        pi = &data;
    }

    A(const A& a)
    {
        cout << "copy constructor!" << endl;
        data = a.data;
        pi = &data;
    }

    A(A&& a)
    {
        cout << "move constructor!" << endl;
        pi = a.pi;
        data = a.data;

        a.pi = NULL;
        a.data = 0;
    }

    A& operator+(const A& a)
    {
        cout << "operator+ called!" << endl;
        this->data += a.data;

        return *this;
    }

    A& operator=(const A& a)
    {
        cout << "operator= called!" << endl;
        this->data = a.data;
        this->pi = a.pi;

        return *this;
    }

    A& operator=(A&& a)
    {
        cout << "move operator= called!" << endl;
        this->data = a.data;
        this->pi = a.pi;

        a.data = 0;
        a.pi = nullptr;

        return *this;
    }


    void show() const
    {
        cout << "pi=" << pi << " data=" << data << endl;
    }

private:
    int data;
    int *pi;
};


int main()
{
    int i = 99;

    //normal constructor
    A a(10);
    a.show();

    A b(i);
    b.show();

    //copy constructor
    A c(b);
    c.show();

    //copy constructor
    A d(b+c);
    d.show();

    //move constructor
    A e = std::move(d);
    e.show();
    d.show();


    A f(std::move(e));
    f.show();

    A g(2);
    g.show();
    g = std::move(f);
    g.show();

}
