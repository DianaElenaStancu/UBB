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

def test_create_person():
    p = Person('John', 'Str Zorilor Nr 12')
    assert (p.getName() == 'John')
    assert (p.getPersonID() == 1)
    assert (p.getAddress() == 'Str Zorilor Nr 12')

    p.setName('Tom')
    assert (p.getName() == 'Tom')
    assert (p.getPersonID() == 1)
    assert (p.getAddress() == 'Str Zorilor Nr 12')

    p.setAddress('Str Viorelelor Nr 14')
    assert (p.getName() == 'Tom')
    assert (p.getPersonID() == 1)
    assert (p.getAddress() == 'Str Viorelelor Nr 14')

    p1 = Person('Tom', 'Str Oilor Nr 12')
    assert(p.getPersonID() == 1)
    assert(p1.getPersonID() == 2)


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
        return "EventID: " + str(self.__eventID) + "; Date: " + self.__date + "; Time: " + self.__time + "; Description: " + self.__description

def test_create_event():
    e = Event(date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
    assert (e.getEventID() == 1)
    assert (e.getTime() == time(16,0,0,0))
    assert (e.getDate() == date(2020, 11, 30))
    assert (e.getDescription() == "botezul Anei")

    e.setDate(date(2021, 11, 30))
    assert (e.getEventID() == 1)
    assert (e.getTime() == time(16,0,0,0))
    assert (e.getDate() == date(2021, 11, 30))
    assert (e.getDescription() == "botezul Anei")

    e.setTime(time(18,0,0,0))
    assert (e.getEventID() == 1)
    assert (e.getTime() == time(18,0,0,0))
    assert (e.getDate() == date(2021, 11, 30))
    assert (e.getDescription() == "botezul Anei")

    e.setDescription("nunta lui Marcel si Eva")
    assert (e.getEventID() == 1)
    assert (e.getTime() == time(18,0,0,0))
    assert (e.getDate() == date(2021, 11, 30))
    assert (e.getDescription() == "nunta lui Marcel si Eva")

    e2 = Event(date(2023, 11, 30), time(19, 0, 0, 0), "majorat Maria")
    assert (e.getEventID() == 1)
    assert (e2.getEventID() == 2)


