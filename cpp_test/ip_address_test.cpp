#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sstream>

using namespace std;


std::string toString(struct in_addr ipv4Address)
{
    std::ostringstream os;
    char               addr4buf[16]; // big enough for IPv4
    //char               addr6buf[46]; // big enough for IPv6


    if (inet_ntop(AF_INET, &ipv4Address, addr4buf, sizeof(addr4buf)) == 0)
    {
	os << "Illegal_v4_IpAddress";
    }
    os << addr4buf;
	
    return os.str();
/*
    switch (ipAddressType_)
    {
        case Network::IpAddress::IPv4:
            if (::inet_ntop(AF_INET, &getAddressIpv4(), addr4buf, sizeof(addr4buf)) == 0)
            {
                os << "Illegal_v4_IpAddress";
            }
            os << addr4buf;
            break;

        case Network::IpAddress::IPv6:
            if (::inet_ntop(AF_INET6, &getAddressIpv6(), addr6buf, sizeof(addr6buf)) == 0)
            {
                os << "Illegal_v6_IpAddress";
            }
            os << addr6buf;
            break;

        default:
            os << "Invalid_IpAddress";
            break;
    }

    return os.str();
*/
}

int main()
{
	struct in_addr  ipv4Address;
	ipv4Address.s_addr = 2148703754;
	string address = toString(ipv4Address);
	cout << address << endl;

	ipv4Address.s_addr = 2148703242;
	address = toString(ipv4Address);
	cout << address << endl;
}
