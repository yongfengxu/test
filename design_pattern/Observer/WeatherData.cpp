#include "WeatherData.h"

void WeatherData::attach(IObserver* o)
{
    observers.emplace_back(o);
}

void WeatherData::detach(IObserver* o)
{
    observers.remove(o);
}

void WeatherData::update()
{
    for(const auto& o: observers)
    {
        o->display(state_);
    }
}

void WeatherData::setState(int s)
{
    state_ = s;
    update();
}
