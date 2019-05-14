#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
#include <map>

struct B {
  virtual void bar() { std::cout << "B::bar\n"; }
  virtual ~B() = default;
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};

// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}

void close_file(std::FILE* fp)
{
    std::fclose(fp);
}

typedef std::map<int, D> MyMap;

std::unique_ptr<MyMap> fun1()
{
    std::unique_ptr<MyMap> mm(new MyMap());

    return mm;
}

int main()
{

    //auto p = std::make_unique<MyMap>(new MyMap());
    auto p = fun1();
    if (p)
    {
        std::cout << "p is not null" << std::endl;
    }


    if (p->empty())
    {
        std::cout << "p is empty" << std::endl;
    }
    else
    {
        std::cout << "p is not empty" << std::endl;
    }

    std::cout << p->size() << std::endl;

  std::cout << "unique ownership semantics demo\n";
  {
      auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
      auto q = pass_through(std::move(p)); 
      assert(!p); // now p owns nothing and holds a null pointer
      q->bar();   // and q owns the D object
  } // ~D called here

  std::cout << "Runtime polymorphism demo\n";
  {
    std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
                                                  // as a pointer to base
    p->bar(); // virtual dispatch

    std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
    v.push_back(std::make_unique<D>());
    v.push_back(std::move(p));
    v.emplace_back(new D);
    for(auto& p: v) p->bar(); // virtual dispatch
  } // ~D called 3 times

  std::cout << "Custom deleter demo\n";
  std::ofstream("demo.txt") << 'x'; // prepare the file to read
  {
      std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"),
                                                           &close_file);
      if(fp) // fopen could have failed; in which case fp holds a null pointer
        std::cout << (char)std::fgetc(fp.get()) << '\n';
  } // fclose() called here, but only if FILE* is not a null pointer
    // (that is, if fopen succeeded)

  std::cout << "Custom lambda-expression deleter demo\n";
  {
    std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });  // p owns D
    p->bar();
  } // the lambda above is called and D is destroyed

  std::cout << "Array form of unique_ptr demo\n";
  {
      std::unique_ptr<D[]> p{new D[3]};
  } // calls ~D 3 times
}


/*
void my_destruction(int* b)
{
    std::cout << "hello " << *b   << "\n"; 
}

bool fun1(std::unique_ptr<int> p)
{
    std::cout << "fun1 " << *p << std::endl;

    std::cout << "fun1 " << (p.get()) << std::endl;
    return true;
}


void fun2(std::unique_ptr<int>& p)
{
    std::cout << "fun2 " << *p << std::endl;

    std::cout << "fun2 " << (p.get()) << std::endl;
}

void fun3(int* p)
{
    std::cout << "fun3 " << *p << std::endl;
    std::cout << "fun3 " << p << std::endl;
}

void fun4(int& value)
{
    std::cout << "fun4 " << value << std::endl;
}




int main()
{

    std::unique_ptr<int> p = std::make_unique<int>(5);
    std::cout << "p address: " << p.get() << std::endl;
    //std::unique_ptr<int, decltype(&my_destruction)> p(new int(5), &my_destruction);

    fun2(p);
    std::cout << *p << std::endl;

    fun3(p.get());

    fun4(*p);

    fun1(std::move(p));
    std::cout << *p << std::endl;
}







*/

