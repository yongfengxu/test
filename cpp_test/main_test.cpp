#include <iostream>


void test1()
{
     int v1, v2;
     std::cin >> v1 >> v2;
     while (v1 <= v2)
     {
          std::cout << v1 << std::endl;
          ++v1;
     }
}

int main()
{
     int n = 50;
     int sum = 0;
     while (n <= 100)
     {
          sum += n;
          ++n;
     }

     std::cout << sum << std::endl;

     n = 10;
     while (n >= 0)
     {
          std::cout << n << std::endl;
          --n;
     }

     n = 0;
     sum = 0;
     while (std::cin >> n)
     {
          sum += n;
     }

     std::cout << sum << std::endl;
}
