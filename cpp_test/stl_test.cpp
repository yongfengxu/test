#include <iostream>
#include <map>

using namespace std;

int main()
{
    using IMap = map<int, int>;


    IMap im1;
    im1.insert(make_pair(1,1));

    IMap im2;
    im2.insert(make_pair(2,2));

    im1.swap(im2);

    for (auto it = im1.begin(); it != im1.end(); ++it)
    {
        std::cout << it->first << ", " << it->second << '\n';
    }
}
