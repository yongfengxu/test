#ifndef ISUBJECT_H_
#define ISUBJECT_H_


class IObserver;

class ISubject
{
public:
    virtual ~ISubject() = default; 
    virtual void attach(IObserver* o) = 0;
    virtual void detach(IObserver* o) = 0;
    virtual void update() = 0;
};


#endif
