#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main() {
  std::random_device rd; // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 10);
  std::vector<int> vi;

  for (int n = 0; n < 100; ++n)
  {
      //std::cout << distrib(gen) << ' ';
    vi.push_back(distrib(gen));
  }

  for(int n = 0; n < 11; ++n)
  {
      int count = std::count(vi.begin(), vi.end(), n);
      std::cout << n << ":" << count << std::endl;
  }

  uint32_t start = std::numeric_limits<uint32_t>::min();

  std::cout << start << std::endl;
}
