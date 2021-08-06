#include <iostream>

class Test
{
public:
    Test(bool flag = false): flag_(flag) {}
    bool getFlag() { return flag_; }
private:
    bool flag_ = false;
};

int main()
{
    Test test(true);
    if (test.getFlag())
    {
        std::cout << "it's true" << std::endl;
    }
}
