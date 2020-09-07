#include <iostream>


class Debug
{
public:
    constexpr Debug(bool flag = true):hw(flag), io(flag), other(flag) {}
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) {}

    constexpr bool any() const {return hw || io || other;}

    void set_hw(bool flag) {hw = flag;}
    void set_io(bool flag) {io = flag;}
    void set_other(bool flag) {other = flag;}

private:
    bool hw;
    bool io;
    bool other;
};

int main()
{
    constexpr Debug io_sub(false, true, false);
    io_sub.set_hw(true);
    if (io_sub.any())
    {
        std::cout << "a ha" << std::endl;
    }

    constexpr Debug prod(false);
    if (prod.any())
    {
        std::cout << "a ha" << std::endl;
    }

}
