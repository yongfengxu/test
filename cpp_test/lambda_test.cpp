#include <iostream>
#include <vector>
#include <functional>

using namespace std;


int main()
{
    int val = 11;
    int tree = 5;

    {
        auto captureVar = [val]() mutable {
            val += 1;
            cout << "val = " << val << endl;
        };

        captureVar();        // val 12
        cout << val << endl; // 11
    }

    {
        val = 11; tree = 5;

        auto f = [&](int b) {
            val += 1;
            tree = b;
            cout << "[&] val = " << val << " b = " << b << endl;
        };

        f(22); // "[&] val = 12, b = 22"

        cout << val << endl;  // 12
        cout << tree << endl; // 22
    }

    {
      val = 11;
      tree = 5;
      auto f1 = [&, tree](int b) mutable {
        val += 1;
        tree = b;
        cout << "[&] val = " << val << " tree = " << tree << endl;
      };

      f1(23); // "[&, tree] val = 12, tree = 23"

      cout << val << endl;  // 12
      cout << tree << endl; // 5
    }

    {
      val = 11;
      tree = 5;
      auto f3 = [=, &tree](int b) mutable {
        val += 1;
        tree = b;
        cout << "[&] val = " << val << " tree = " << b << endl;
      };

      f3(44); // "[&] val = 12, tree = 44"

      cout << val << endl;  // 11
      cout << tree << endl; // 44
    }

    {
        vector<int> xs = {1, 2, 3};

        auto f = [&xs]() {vector<int> p = std::move(xs);};

        cout << xs.size() << endl; //3

        auto g = [p = std::move(xs)]() {};

        cout << xs.size() << endl; //3
    }


}
