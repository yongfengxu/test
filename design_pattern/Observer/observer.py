
class Observable:
	"base class"

	def __init__(self):
		self.__observers = []

	def addObserver(self, observer):
		self.__observers.append(observer)

	def removeObserver(self, observer):
		self.__observers.remove(observer)


	def notifyObservers(self, object = 0):
		for o in self.__observers:
			o.update(self, object)

class Observer:
	def update(self, observer, object):
		pass

class WaterHeater(Observable):
	def __init__(self):
		super().__init__()
		self.__temperature = 25

	def getTemperature(self):
		return self.__temperature

	def setTemperature(self, temperature):
		self.__temperature = temperature
		print ("current temperature is: ", self.__temperature)
		self.notifyObservers()

class WashingMode(Observer):
	def update(self, observable, object):
		if isinstance(observable, WaterHeater) and observable.getTemperature() >= 50 and observable.getTemperature() < 70:
		    print("you can wash now!!")

class DrinkingMode(Observer):
	def update(self, observable, object):
		if isinstance(observable, WaterHeater) and observable.getTemperature() >= 100:
		    print("you can drink now!!")

if __name__ == '__main__':
	heater = WaterHeater()
	washingObser = WashingMode()
	drinkingObser = DrinkingMode()

	heater.addObserver(washingObser)
	heater.addObserver(drinkingObser)

	heater.setTemperature(40)
	heater.setTemperature(60)
	heater.setTemperature(100)


