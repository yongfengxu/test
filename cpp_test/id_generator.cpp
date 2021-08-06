#include <iostream>
#include <vector>

#define BITLIMLENGTH_4K  12
#define CP_BITLIMLENGTH BITLIMLENGTH_4K
#define MAX_CP_BITLIMLENGTH (CP_BITLIMLENGTH)
#define MAX_NO_OF_CP_LOAD_INDEXES (1 << MAX_CP_BITLIMLENGTH)

constexpr uint32_t MAX_ID_BY_LOADINDEX = (1 << (31 - MAX_CP_BITLIMLENGTH));
std::vector<uint32_t> idContainer(MAX_NO_OF_CP_LOAD_INDEXES, 0);

uint32_t getNextIdByLoadIndex(uint16_t loadIndex)
{
    idContainer[loadIndex]++;

    if (idContainer[loadIndex] >= MAX_ID_BY_LOADINDEX)
    {
        idContainer[loadIndex] = 0;
    }

    return ((idContainer[loadIndex] << MAX_CP_BITLIMLENGTH) | loadIndex);
}


int main()
{
    std::cout << MAX_NO_OF_CP_LOAD_INDEXES << std::endl;

    std::cout << getNextIdByLoadIndex(1004) << std::endl;

}
