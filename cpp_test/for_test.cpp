#include <iostream>
#include <map>
#include <string>


struct Node
{
    int ip;
    int port;
};

int main()
{
    std::map<std::string, Node> aMap;
    aMap["hello"] = {1, 2};

    for (const auto& [_, value] : aMap)
    {
        std::cout << value.ip << " " << value.port << std::endl;
    }


}
