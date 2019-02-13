#include "IObservable.h"
#include "IObserver.h"
#include <list>
#include <memory>

class WeatherData : public IObservable
{
public:
    WeatherData() : state_(0), changed_(false) {}
    ~WeatherData() {}

    void attach(IObserver* o) override;
    void detach(IObserver* o) override;
    void notify() override;
    void setChanged(bool flag) override;

    void setState(int s);

private:
    int state_;
    bool changed_;
    std::list<IObserver*> observers;

};
