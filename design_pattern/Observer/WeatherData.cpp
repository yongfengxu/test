#include "WeatherData.h"

void WeatherData::attach(IObserver* o)
{
    observers.emplace_back(o);
}

void WeatherData::detach(IObserver* o)
{
    observers.remove(o);
}

void WeatherData::notify()
{
    if (changed_)
    {
        for(const auto& o: observers)
        {
            o->display(state_);
        }

        setChanged(false);
    }

}

void WeatherData::setChanged(bool flag)
{
    changed_ = flag;
}

void WeatherData::setState(int s)
{
    state_ = s;
    setChanged(true);
    notify();
}
