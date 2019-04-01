#include <iostream>
#include <string>

class I
{
public:
    static I* getInstance();
    ~I() = default;
    void show() {std::cout << name_ << " " << age_ << std::endl;}
    void setAge(unsigned age) {age_ = age;}

private:
    I(std::string name, unsigned age) : name_(name), age_(age) {}

    static I* myself_;
    std::string name_;
    unsigned age_;
};

I* I::myself_ = nullptr;

I* I::getInstance()
{
    if (I::myself_ == nullptr)
    {
        I::myself_ = new I("charlie", 32);
    }

    return I::myself_;
}


int main()
{
    I* m1 = I::getInstance();

    m1->show();

    I* m2 = I::getInstance();
    m2->setAge(34);
    m2->show();

    I* m3 = I::getInstance();
    m3->setAge(36);
    m3->show();

    delete m1; 

}
