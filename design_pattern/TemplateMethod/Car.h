#ifndef CAR_H_
#define CAR_H_
#include "ICar.h"

class BMW : public ICar
{
public:
    void setSequenceNumber(unsigned num) override;
protected:
    void start() override;
    void ring() override;
    void go() override;

    //hook
    bool isAlarm() override;
};

class Audi : public ICar
{
public:
    Audi():isAlarm_(true) {}
    void setAlarm(bool alarm);

    void setSequenceNumber(unsigned num) override;
protected:
    void start() override;
    void ring() override;
    void go() override;

    //hook
    bool isAlarm() override;

private:
    bool isAlarm_;
};


#endif

