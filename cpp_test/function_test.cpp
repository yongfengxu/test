#include <iostream>
#include <set>
#include <string>
#include <cstdint>

int main()
{

    //std::cout << "INT_MAX is " << INT_MAX << "UINT_MAX is " << UINT_MAX;

    {
        std::string str = "3066700000";
        unsigned i = std::stoi(str.c_str());
        std::cout << i << std::endl;
    }

    {
        std::set<uint16_t> tacSet;
        const char* str = "3066700000";

        try
        {
            tacSet.emplace(std::stoi(str));
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "out_of_range " << e.what() << std::endl;
        }

        for (auto value : tacSet)
        {
            std::cout << value << std::endl;
        }
    }

}
