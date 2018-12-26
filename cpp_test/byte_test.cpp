#include <iostream>

#include <inttypes.h>
#include <stdint.h>

using namespace std;

int main()
{
    uint8_t num = 0xFF;

    cout << static_cast<int>(num) << endl;

    num++;

    cout << static_cast<int>(num) << endl;


}
