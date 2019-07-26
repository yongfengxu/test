#include <iostream>
#include <bitset>


using namespace std;

int main()
{
    using ApplyActions = std::bitset<8>;


    ApplyActions actions("0101");

    if (actions.test(0))
    {
        cout << "bit 0 is 1" << endl;
    }

    std::cout << "size = " << actions.size() << std::endl;





}
