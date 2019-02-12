#include "WeatherData.h"
#include "ConcreteObserver.h"

int main()
{
    std::unique_ptr<WeatherData> weather = std::make_unique<WeatherData>();

    std::unique_ptr<ConcreteObserver> ob1 = std::make_unique<ConcreteObserver>("ob1", static_cast<ISubject*>(weather.get()));
    std::unique_ptr<ConcreteObserver> ob2 = std::make_unique<ConcreteObserver>("ob2", static_cast<ISubject*>(weather.get()));

    ob2->subscribe();
    weather->setState(1);

    ob1->subscribe();
    weather->setState(2);

    ob2->unsubscribe();
    weather->setState(3);


}
