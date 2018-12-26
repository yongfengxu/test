#include <iostream>

void lock(Mutex* pm);
void unlock(Mutex* pm);

class Lock
{
public:
    explicit Lock(Mutex* pm): mutexPtr(pm)
    {
        lock(mutexPtr);
    }
    ~Lock() {unlock(mutexPtr);}

private:
    Mutex *mutexPtr;
};



Mutex m;
...
{
    Lock m1(&m);
    ...

}

class Lock
{
public:
    explicit Lock(Mutex* pm): mutexPtr(pm, unlock)
    {
        lock(mutexPtr.get());
    }



private:
    std::shared_ptr<Mutex, decltype(&unlock)> mutexPtr;
};
