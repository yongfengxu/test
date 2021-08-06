#include <iostream>


char data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

int main()
{
    uint32_t value = (*reinterpret_cast<uint32_t*>(data + 1));


    std::cout << value << std::endl;


}
