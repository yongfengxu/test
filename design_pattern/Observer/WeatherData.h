#include "ISubject.h"
#include "IObserver.h"
#include <list>
#include <memory>

class WeatherData : public ISubject
{
public:
    WeatherData() : state_(0) {}
    ~WeatherData() {}
    void attach(IObserver* o) override;
    void detach(IObserver* o) override;
    void update() override;
    void setState(int s);

private:
    int state_;
    std::list<IObserver*> observers;

};
