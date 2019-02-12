#include "IObserver.h"
#include <memory>
#include <string>

class ISubject;

class ConcreteObserver: public IObserver
{
public:
    ConcreteObserver(std::string name, ISubject* subject);
    ~ConcreteObserver();
    void display(int state) override;

    void setSubject(ISubject* subject);

    void subscribe();
    void unsubscribe();

private:
    std::string name_;
    ISubject* subject_;

};
