#include <iostream>
#include <sstream>

int main()
{

    int value = 0x18;
    std::stringstream os;
    os << std::hex << value;

    std::cout << os.str() << std::endl;

}
