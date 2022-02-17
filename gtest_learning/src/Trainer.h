#include "IBird.h"

class Trainer
{
public:
    Trainer(IBird& b):bird(b) {}
    void show() {bird.fly(10);}

private:
    IBird& bird;
};
