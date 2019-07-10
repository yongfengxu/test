#include <iostream>
#include <utility>

using namespace std;

struct M2 {   // bad: incomplete set of default operations
public:
    // ...
    // ... no copy or move operations ...
    ~M2()
    {
        cout << "delete rep" << endl;
        delete rep;
        rep = nullptr;
    }
private:
    int* rep = new int(1);
};

int main()
{
    M2 x;
    M2 y;
    // ...
    x = y;   // the default assignment
    // ...
}
