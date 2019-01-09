#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class A;
using myVec = std::vector<A*>;
using myVecS = std::vector<std::unique_ptr<A> >;

class A
{
};

void address_sanitizer_memory_leak()
{
    myVec vec;
    vec.push_back(new A());

    auto a = std::make_unique<A>();

    vec.push_back(static_cast<A*>(a.release()));

    //memory leak if no destruct, if we take the ownership of pointer, we should destruct it
    //for_each(vec.begin(), vec.end(), std::default_delete<A>());
}

void address_sanitizer_good()
{
    myVecS vecs;
    vecs.push_back(std::make_unique<A>());
    vecs.push_back(std::make_unique<A>());
    vecs.push_back(std::make_unique<A>());
    vecs.push_back(std::make_unique<A>());
}

void address_sanitizer_double_free()
{
    myVec vec;

    auto a = std::make_unique<A>();
    auto a2 = std::make_unique<A>();
    vec.push_back(static_cast<A*>(a.release()));
    vec.push_back(static_cast<A*>(a2.get()));

    //memory leak if no destruct, if we take the ownership of pointer, we should destruct it
    for_each(vec.begin(), vec.end(), std::default_delete<A>());
}

int main()
{
    //address_sanitizer_memory_leak();
    address_sanitizer_double_free();
    address_sanitizer_good();
}













