#include <iostream>
#include <vector>

class NoDefault
{
public:
    NoDefault(int i) : num(i) {}
    int getValue() const {return num;}
private:
    int num;
};

class C
{
public:
    friend std::ostream& operator<<(std::ostream& os, const C& c);
    C() : my_mem(11) {};
    NoDefault my_mem;
};

std::ostream& operator<<(std::ostream&os, const C& c)
{
    os << "Charlie:" << c.my_mem.getValue();
    return os;
}

int main()
{
    C c;
    //std::vector<NoDefault> vev(10);
    std::vector<C> vec(10);

    for (const auto value : vec)
    {
        std::cout << value << std::endl;
    }
}

