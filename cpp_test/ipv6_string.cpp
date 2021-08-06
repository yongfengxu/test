#include <string>
#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdint>
#include <sstream>

int main()
{
std::string data = "0000000000000001";
struct in6_addr addr;
char   addr6buf[46] {0};
addr.__in6_u.__u6_addr32[0] = 0;
addr.__in6_u.__u6_addr32[1] = 0;
std::istringstream is(data);
is.seekg(0);
char d[2];
for (int i =0; i < 8; ++i)
{
if (is.read(d, 2))
{
std::sscanf(d, "%02X", &addr.__in6_u.__u6_addr8[i+8]);
std::cout<< static_cast<int>(addr.__in6_u.__u6_addr8[i+8]) << std::endl;
}
else
{
std::cout<< "fuck"<< std::endl;
break;
}
}

 

inet_ntop(AF_INET6, &addr, addr6buf, sizeof(addr6buf));
std::cout << addr6buf << "  " <<addr.__in6_u.__u6_addr32[2] << "  " << addr.__in6_u.__u6_addr32[3] <<std::endl;

 

return 0;
}
