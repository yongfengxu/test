#ifndef IOBSERVER_H_
#define IOBSERVER_H_

class IObserver
{
public:
    virtual ~IObserver();
    virtual void display(int state) = 0;
};

#endif
