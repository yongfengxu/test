#include <iostream>

using namespace std;

void test()
{
    char c[10] = "123456789";
    char* p = &c[1];

    const char* p1 = &c[2];
    const char* const p2 = &c[3];
    char* const p3 = &c[4];

    cout << "---char* p---" << endl;
    cout << "original value = " << *p << endl;
    *p = 'b';
    cout << "after *p = 'b',  value = " << *p << endl;

    cout << "---const char* p1---" << endl;
    cout << "original value = " << *p1 << endl;
    //*p1 = 'b'; //const_test.cpp : 19 : 9 : error : assignment of read - only location ‘*p1’
    p1 = &c[0];
    cout << "after p1 = &c[0], value = " << *p1 << endl;

    cout << "---const char* p2---" << endl;
    cout << "can't do anything, value = " << *p2 << endl;

    cout << "---const char* p3---" << endl;
    cout << "original value = " << *p3 << endl;
    *p3 = 'd';
    //p3 = &c[0];
    cout << "after *p3 = 'd', value = " << *p3 << endl;
}

int main()
{
    int i = 0;
    const int v2 = 0; // top-level const
    int v1 = v2;
    int *p1 = &v1;
    int &r1 = v1;
    const int *p2 = &v2; // low-level const
    const int *const p3 = &i; //low-level const and top-level const
    const int &r2 = v2; // low-level const

    r1 = v2; // legal

    // error: assigning to 'int *' from incompatible type 'const int *'
    // p1 = p2; // p2 has low-level const, p1 doesn't have. so this expression is illegal

    p2 = p1; // p1 doesn't have low-level const, non-const can convert to const

    // error: assigning to 'int *' from incompatible type 'const int *const'
    // p1 = p ; // p3 has low-level const, p1 doesn't have. 
    p2 = p3; // two variables all have low-level const, legal

    int null = 0;
    int *p = &null;
}

