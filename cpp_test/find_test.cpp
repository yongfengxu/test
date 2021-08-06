#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
 
void test1()
{
    std::vector<int> v{1, 2, 3, 4};
    int n1 = 3;
    int n2 = 5;
    auto is_even = [](int i){ return i%2 == 0; };
 
    auto result1 = std::find(begin(v), end(v), n1);
    auto result2 = std::find(begin(v), end(v), n2);
    auto result3 = std::find_if(begin(v), end(v), is_even);
 
    (result1 != std::end(v))
        ? std::cout << "v contains " << n1 << '\n'
        : std::cout << "v does not contain " << n1 << '\n';
 
    (result2 != std::end(v))
        ? std::cout << "v contains " << n2 << '\n'
        : std::cout << "v does not contain " << n2 << '\n';
 
    (result3 != std::end(v))
        ? std::cout << "v contains an even number: " << *result3 << '\n'
        : std::cout << "v does not contain even numbers\n";
}

bool find_serving_scope(std::vector<std::string>& servingScope, std::vector<std::string>& subServingScopes)
{
    for (const auto& item: subServingScopes)
    {
        if (std::find(servingScope.begin(), servingScope.end(), item) == servingScope.end())
        {
            return false;
        }
    }

    return true;

    // std::sort(servingScope.begin(), servingScope.end());
    // std::sort(subServingScopes.begin(), subServingScopes.end());

    // return std::includes(servingScope.begin(), servingScope.end(), subServingScopes.begin(), subServingScopes.end());

}

int main()
{
    std::vector<std::string> ss;
    // ss.push_back("hnQs2");
    // ss.push_back("Hnqs2");
    // ss.push_back("HNQs2");

    std::vector<std::string> sss;
    sss.push_back("hbqs2");

    if (find_serving_scope(ss,sss))
    {
        std::cout << "find it" << std::endl;
    }
    else
    {
        std::cout << "don't find it" << std::endl;
    }
}
