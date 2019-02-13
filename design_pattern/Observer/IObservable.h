#ifndef IOBSERVABLE_H_
#define IOBSERVABLE_H_


class IObserver;

class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void attach(IObserver* o) = 0;
    virtual void detach(IObserver* o) = 0;

    virtual void notify() = 0;

    virtual void pullSomething(IObserver& o) = 0;

    virtual void setChanged(bool flag) = 0;
};


#endif
