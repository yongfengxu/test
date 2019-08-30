#include <iostream>
#include <bitset>


using namespace std;
enum class ApplyActionValue : uint32_t
{
    DROP = 1,
    FORD = 2,
    BUFF = 4,
    NOCP = 8,
    BUFFNOCP = 12,
    DUPL = 16
};

using ApplyActions = std::bitset<8>;

void fun(const ApplyActions actions)
{
    if (actions.test(0))
    {
        cout << "bit 0 is 1" << endl;
    }
}

int main()
{


    ApplyActions actions("0101");

    if (actions.test(0))
    {
        cout << "bit 0 is 1" << endl;
    }

    std::cout << "size = " << actions.size() << std::endl;


    fun(ApplyActions(static_cast<uint32_t>(ApplyActionValue::BUFFNOCP)));



}
