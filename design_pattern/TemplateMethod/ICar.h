#ifndef ICAR_H_
#define ICAR_H_

class ICar
{
public:
    virtual ~ICar() = default;

    ICar():num_(0) {}
    //template method
    void run();
    virtual void setSequenceNumber(unsigned num) = 0;

protected:
    virtual void start() = 0;
    virtual void ring() = 0;
    virtual void go() = 0;
    virtual bool isAlarm() = 0;

    unsigned num_;

};


#endif
