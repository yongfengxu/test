#ifndef ICAR_H_
#define ICAR_H_

class ICar
{
public:
    virtual ~ICar() = default;

    //template method
    void run();

protected:
    virtual void start() = 0;
    virtual void ring() = 0;
    virtual void go() = 0;
    virtual bool isAlarm() = 0;

};


#endif
