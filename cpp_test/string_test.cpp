#include <iostream>
#include <string>

void print(std::string::size_type n, std::string const &s) {
  if (n == std::string::npos) {
    std::cout << "not found\n";
  } else {
    std::cout << "found: " << s.substr(n) << '\n';
  }
}

int main() {
  std::string::size_type n;
  std::string const s = "1:9000:X1 connection to admf001 recovered at xx:xx:xx yy:yy:yy";


  // find a single character
  n = s.find(':');
  std::cout << "first : is " << n << std::endl;

  n = s.find(':', n + 1);
  std::cout << "second : is " << n << std::endl;

  std::cout << "third part string is " << s.substr(n+1) << std::endl;
}
