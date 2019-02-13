#include "IObserver.h"
#include <memory>
#include <string>

class IObservable;

class ConcreteObserver: public IObserver
{
public:
    ConcreteObserver(std::string name, IObservable* observable);
    ~ConcreteObserver();

    void display(int state) override;
    void activeDisplay(int state) override;

    void setObservable(IObservable* observable);
    void requestSomething();

    void subscribe();
    void unsubscribe();

private:
    std::string name_;
    IObservable* observable_;

};
