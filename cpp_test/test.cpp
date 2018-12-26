#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <boost/tuple/tuple_comparison.hpp>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/lexical_cast.hpp>

using namespace std;

//typedef unsigned char		uint8_t;

#define pdp_CreateState_names \
	C(PDP_ST_INIT)		\
	C(PDP_ST_DHCP_CLIENT) \

#define C(x) x,
enum pdp_CreateState_t
{
	pdp_CreateState_names
	PDP_ST_NB_CREATE
};
#undef C

#define C(x) #x,
	static const char* const names[] = {pdp_CreateState_names};
#undef C

class A
{
public:
	A():a(), b(), c() {}
	void print() const {cout << a << ' ' << b << ' ' << c << endl;}

private:
	int a;
	long b;
	float c;
};

void test_tie()
{
	int i = 0;
	int a = 6, b = 1, c = 3, d = 4;
	printf("hello world! %d\n", PDP_ST_NB_CREATE);

	for ( i = 0; i < PDP_ST_NB_CREATE; ++i)
	{
		printf("==%s==\n", names[i]);
	}

	printf("%d\n", boost::tie(a, b) < boost::tie(c, d));

	A obj;
	obj.print();
}

#define ServiceManagerServices\
	C(PpbService)		\
	C(S5Service)

	
void test_macro()
{
	#define C(Name) Name Name##_;
	C(int)
	#undef C
	int_ = 1;
	cout << int_ << endl;
}

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t Sm_State_t; 

void bit_test(Sm_State_t* pState)
{
	uint8_t StateMachine, State;
	StateMachine            = ((*pState) & 0xFF00) >> 8;
    	State                   = ((*pState) & 0xFF);

	cout << "StateMachine = " << StateMachine << " State = " << State << endl;

}

enum Type
{
INTERNAL_CAUSE_INVALID,
INTERNAL_CAUSE_ACCEPT

};

static const char* codeAsString(const Type cause)
{
#define CC_CHECK(cause) case cause: return(#cause)
#define CC_CHECK_BASE_COMMON(cause, commonCause) case cause: return(/*"base-cause*/ #cause)

	switch (cause)
	{
		CC_CHECK(INTERNAL_CAUSE_INVALID);
		CC_CHECK_BASE_COMMON(INTERNAL_CAUSE_ACCEPT, 2);
	
	}

}

#if 0
uint32_t dbp_Avp_DecodeOctetString(const char* buf, const char** rv_string, uint32_t* rv_string_len)
{
    AvpHdr    avp;
    uint32_t  hdr_len;
    uint32_t  pad_len;
    uint32_t* u32p;

    memcpy(&avp, buf, sizeof(AvpHdr));

    u32p  = (uint32_t*)&avp;

    *u32p = ntohl(*u32p); u32p++;
    *u32p = ntohl(*u32p);

    if (!avp.v)
        hdr_len = sizeof(AvpHdr);
    else
        hdr_len = sizeof(AvpHdr) + sizeof(uint32_t);

    *rv_string     = buf + hdr_len;
    *rv_string_len = avp.length - hdr_len;

    pad_len        = avp.length % 4;
    if (pad_len != 0)
        pad_len = 4 - pad_len;

    return avp.length + pad_len;
}
#endif

void boost_test()
{
	uint32_t praId = 111111;
	uint8_t id;
	const std::string temp = boost::lexical_cast<std::string>(praId);
	cout << "boost_test():" << temp << endl;
	//uint8_t *p = reinterpret_cast<const uint8_t*>(temp);

	//printf("%c %c %c \n", (uint8_t)p, uint8_t(p + 1), uint8_t(p + 2));
}

int main()
{
//	test_macro();
	Sm_State_t st = 0x4161;
	bit_test(&st);

	cout << "what i want is :" << codeAsString(INTERNAL_CAUSE_ACCEPT) << endl;

	printf("%x \n", htons(0x0010));
	printf("%x \n", (0x0010));

	boost_test();	
	uint8_t id[3] = {0x00, 0xDF, 0xFF};
        uint32_t tmpId = 0;
        memcpy((uint8_t*)&tmpId, (uint8_t*)id, 3);

	uint8_t* p = (uint8_t*)&tmpId;

	printf("%c %c %c %c\n", (*p), *(p+1), *(p+2), *(p+3));
}
