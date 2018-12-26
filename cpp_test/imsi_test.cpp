#include <iostream>
#include <arpa/inet.h>

using namespace std;
typedef unsigned long int	uint64_t;
typedef uint64_t u64;
typedef uint16_t u16;
typedef uint32_t u32;

u64 ntohq_(u64 x);
u64 htonq_(u64 x);

u64 htonq_(u64 x)
{
    u64 res;

    u16 tst = 0x00ff;
    if (htons(tst) != tst)
    {
        u32 hi = x >> 32;
        u32 lo = x & 0xffffffff;
        hi  = htonl(hi);
        res = htonl(lo);
        res = res << 32 | hi;

        return res;
    }
    else
    {
        return x;
    }
}

u64 ntohq_(u64 x)
{
    return htonq_(x);
}



int main()
{
	u64 x = 17820787226313922148UL;	

	u64 value = ntohq_(x);


	cout << "imsi = " << value << endl;

}
