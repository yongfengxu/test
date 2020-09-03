#include <iostream>
#include <vector>

int txt_size()
{
    return 11;
}

int main()
{
    unsigned buffer_size = 10;

    int a1[buffer_size];
    int a2[txt_size()];
    int a3[4*6-2];

    //char a[5] = "hello";

    std::vector<int> vv = {1, 2, 3};

    std::cout << *vv.begin() << std::endl;
    std::cout << *(vv.begin()) << std::endl;

    std::cout << *vv.begin() + 1 << std::endl;
    std::cout << *(vv.begin()) + 1 << std::endl;

    unsigned short ss = 32767;

    ss += 1;
    std::cout << "ss = " << ss << std::endl;
}
