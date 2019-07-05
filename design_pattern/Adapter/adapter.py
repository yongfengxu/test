
class IHighPerson:
	def getName(self):
		pass

	def getHeight(self):
		pass

class HighPerson(IHighPerson):
	def __init__(self, name):
		self.__name = name

	def getName(self):
		return self.__name

	def getHeight(self):
		return 170

class ShortPerson:
	def __init__(self, name):
		self.__name = name

	def getName(self):
		return self.__name

	def getRealHeight(self):
		return 160

	def getShoesHeight(self):
		return 6

class PersonAdapter(IHighPerson):

	def __init__(self, person):
		self.__person = person

	def getHeight(self):
		return self.__person.getRealHeight() + self.__person.getShoesHeight()

	def getName(self):
		return self.__person.getName()



def isOk(person):
	if isinstance(person, IHighPerson) and person.getHeight() > 165:
		return "ok"
	else:
		return "nok"

if __name__ == '__main__':

	shortOne = ShortPerson("Lira")
	print (shortOne.getName() + "height is " + str(shortOne.getRealHeight()) + "shoe height is " + str(shortOne.getShoesHeight()) )
	print ("short Person: " + isOk(shortOne))

	highOne = HighPerson("Demi")
	print (highOne.getName() + "height is " + str(highOne.getHeight()) + " " + isOk(highOne))

	decorateOne = PersonAdapter(shortOne)
	print (decorateOne.getName() + "height is " + str(decorateOne.getHeight())+ " " + isOk(decorateOne))
	if isinstance(decorateOne, IHighPerson):
		print ("yes")
	else:
		print ("no")

	

