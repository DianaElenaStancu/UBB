from datetime import date, time

class Person():

    numberOfPersons = 0

    def __init__(self, name, address):
        """
        Initializeaza un obiect de tip persoana cu valorile date
        :param personID: id-ul persoanei
        :type personID: int (>0)
        :param name: numele persoanei
        :type name: str
        :param address: adresa persoanei
        :type address: str
        """
        Person.numberOfPersons += 1
        self.__personID = Person.numberOfPersons
        self.__name = name
        self.__address = address

    def getID(self):
        return self.__personID

    def getName(self):
        return self.__name

    def getAddress(self):
        return self.__address

    def setName(self, value):
        self.__name = value

    def setAddress(self, value):
        self.__address = value

    def __str__(self):
        return "PersonID: " + str(self.__personID) + "; Name: " + self.__name + "; Address: " + self.__address

    def __eq__(self, other):
        return self.getID() == other.getID()

class Event():

    numberOfEvents = 0

    def __init__(self, date, time, description):
        """
        Initializeaza un obiect de tip eveniment cu valorile date
        :param eventID: id-ul evenimentului
        :type eventID: int
        :param date: data la care are loc evenimentul
        :type date: date
        :param time: ora la care are loc evenimentul
        :type time: time
        :param description: descrierea evenimentului
        :type description: str
        """
        Event.numberOfEvents += 1
        self.__eventID = Event.numberOfEvents
        self.__date = date
        self.__time = time
        self.__description = description

    def getID(self):
        return self.__eventID

    def getDate(self):
        return self.__date

    def getTime(self):
        return self.__time

    def getDescription(self):
        return self.__description

    def setDate(self, value):
        self.__date = value

    def setTime(self, value):
        self.__time = value

    def setDescription(self, value):
        self.__description = value

    def __str__(self):
        return "EventID: " + str(self.__eventID) + "; Date: " + str(self.__date) + "; Time: " + str(self.__time) + "; Description: " + self.__description

    def __eq__(self, other):
        return self.getID() == other.getID()

class Participation:
    def __init__(self, person, event):
        self.__person = person
        self.__event = event

    def getPerson(self):
        return self.__person

    def getEvent(self):
        return self.__event

    def setPerson(self, value):
        self.__person = value

    def setEvent(self, value):
        self.__event = value

    def __eq__(self, other):
        return self.getPerson() == other.getPerson() and self.getEvent() == other.getEvent()






