#include <iostream>
using namespace std;
int main()
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
