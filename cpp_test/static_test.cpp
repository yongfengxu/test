#include <iostream>
#include <map>
#include <vector>

using namespace std;


class Test
{
public:
    void show() {cout << num << endl;}
    static const int getNum() {return num;}
    static const int getPI() { return PI; }
    static void setMap1() {myMap1[1] = 2; myMap1[2] = 3;}
    static void setMap2() {
      myMap2[1] = 5;
      myMap2[2] = 6;
    }

    static void setMap3() {
      myMap3[1] = 7;
      myMap3[2] = 8;
    }

    static map<int, int>& getMap1() {return myMap1;}
    static map<int, int> &getMap2() { return myMap2; }
    static map<int, int> &getMap3() { return myMap3; }

  private:
    static const double PI;
    static const int num = 3;

    static map<int, int> myMap1;
    static map<int, int> myMap2;
    static map<int, int> myMap3;
};

const double Test::PI = 3.14;
map<int, int> Test::myMap1;
map<int, int> Test::myMap2;
map<int, int> Test::myMap3;

class Example
{
public:
    static constexpr double rate = 2.5;
    static constexpr int vsize = 20;
    //static std::vector<int> v(2);

};

int main()
{

    Test test;

    test.show();

    int a = Test::getNum();
    cout << a << endl;

    Test::setMap1();
    Test::setMap2();
    Test::setMap3();

    /*
    map<int, int>& mm1 = Test::getMap1();
    map<int, int>& mm2 = Test::getMap2();
    map<int, int>& mm3 = Test::getMap3();


    for (auto iter : mm1)
    {
        cout << iter.first << " " << iter.second << endl;
    }

    for (auto iter : mm2) {
      cout << iter.first << " " << iter.second << endl;
    }

    for (auto iter : mm3) {
      cout << iter.first << " " << iter.second << endl;
    }
    */

    vector<map<int, int>> v;
    v.emplace_back(Test::getMap1());
    v.emplace_back(Test::getMap2());
    v.emplace_back(Test::getMap3());

    for (auto m : v)
    {
        cout << "map" << endl;
        for (auto iter : m)
            cout << iter.first << " " << iter.second << endl;
    }

    return 0;
}

