from app.domain.entities import Person, Event, Participation, Participation_v1
from datetime import date, time
import unittest

class TestEntities(unittest.TestCase):
    def setUp(self) -> None:
        #code executed before every testMethod
        self.__p = Person(1, 'John', 'Str Zorilor Nr 12')
        self.__p1 = Person(2, 'Tom', 'Str Oilor Nr 12')
        self.__e = Event(1, date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
        self.__e1 = Event(2, date(2023, 11, 30), time(19, 0, 0, 0), "majorat Maria")



    def test_create_person(self):
        assert (self.__p.getName() == 'John')
        assert (self.__p.getID() == 1)
        assert (self.__p.getAddress() == 'Str Zorilor Nr 12')

        self.__p.setName('Tom')
        assert (self.__p.getName() == 'Tom')
        assert (self.__p.getID() == 1)
        assert (self.__p.getAddress() == 'Str Zorilor Nr 12')

        self.__p.setAddress('Str Viorelelor Nr 14')
        assert (self.__p.getName() == 'Tom')
        assert (self.__p.getID() == 1)
        assert (self.__p.getAddress() == 'Str Viorelelor Nr 14')

        assert(self.__p.getID() == 1)
        assert(self.__p1.getID() == 2)

    def test_create_event(self):
        assert (self.__e.getID() == 1)
        assert (self.__e.getTime() == time(16,0,0,0))
        assert (self.__e.getDate() == date(2020, 11, 30))
        assert (self.__e.getDescription() == "botezul Anei")

        self.__e.setDate(date(2021, 11, 30))
        assert (self.__e.getID() == 1)
        assert (self.__e.getTime() == time(16,0,0,0))
        assert (self.__e.getDate() == date(2021, 11, 30))
        assert (self.__e.getDescription() == "botezul Anei")

        self.__e.setTime(time(18,0,0,0))
        assert (self.__e.getID() == 1)
        assert (self.__e.getTime() == time(18,0,0,0))
        assert (self.__e.getDate() == date(2021, 11, 30))
        assert (self.__e.getDescription() == "botezul Anei")

        self.__e.setDescription("nunta lui Marcel si Eva")
        assert (self.__e.getID() == 1)
        assert (self.__e.getTime() == time(18,0,0,0))
        assert (self.__e.getDate() == date(2021, 11, 30))
        assert (self.__e.getDescription() == "nunta lui Marcel si Eva")


        assert (self.__e.getID() == 1)
        assert (self.__e1.getID() == 2)

    def test_create_participation(self):
        i = Participation(self.__p, self.__e)
        assert (i.getPerson() == self.__p)
        assert (i.getEvent() == self.__e)

        i.setPerson(self.__p1)
        assert (i.getPerson() == self.__p1)
        assert (i.getEvent() == self.__e)

        i.setEvent(self.__e1)
        assert (i.getPerson() == self.__p1)
        assert (i.getEvent() == self.__e1)

    def test_create_participation_v1(self):
        person_repo = Person
        i = Participation_v1(1, 2)
        assert (i.getPersonID() == 1)
        assert (i.getEventID() == 2)

        i = Participation_v1(2, 7)
        assert (i.getPersonID() == 2)
        assert (i.getEventID() == 7)

if __name__ == '__main__':
    unittest.main()