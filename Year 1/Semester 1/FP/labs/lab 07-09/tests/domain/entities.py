from app.domain.entities import Person, Event, Participation, Participation_v1
from datetime import date, time

class entities_TEST():
    def run(self):
        self.__test_create_person()
        self.__test_create_event()
        self.__test_create_participation()
        self.__test_create_participation_v1()

    def __test_create_person(self):
        p = Person(1, 'John', 'Str Zorilor Nr 12')
        p1 = Person(2, 'Tom', 'Str Oilor Nr 12')
        assert (p.getName() == 'John')
        assert (p.getID() == 1)
        assert (p.getAddress() == 'Str Zorilor Nr 12')

        p.setName('Tom')
        assert (p.getName() == 'Tom')
        assert (p.getID() == 1)
        assert (p.getAddress() == 'Str Zorilor Nr 12')

        p.setAddress('Str Viorelelor Nr 14')
        assert (p.getName() == 'Tom')
        assert (p.getID() == 1)
        assert (p.getAddress() == 'Str Viorelelor Nr 14')

        assert(p.getID() == 1)
        assert(p1.getID() == 2)

    def __test_create_event(self):
        e = Event(1, date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
        e1 = Event(2, date(2023, 11, 30), time(19, 0, 0, 0), "majorat Maria")
        assert (e.getID() == 1)
        assert (e.getTime() == time(16,0,0,0))
        assert (e.getDate() == date(2020, 11, 30))
        assert (e.getDescription() == "botezul Anei")

        e.setDate(date(2021, 11, 30))
        assert (e.getID() == 1)
        assert (e.getTime() == time(16,0,0,0))
        assert (e.getDate() == date(2021, 11, 30))
        assert (e.getDescription() == "botezul Anei")

        e.setTime(time(18,0,0,0))
        assert (e.getID() == 1)
        assert (e.getTime() == time(18,0,0,0))
        assert (e.getDate() == date(2021, 11, 30))
        assert (e.getDescription() == "botezul Anei")

        e.setDescription("nunta lui Marcel si Eva")
        assert (e.getID() == 1)
        assert (e.getTime() == time(18,0,0,0))
        assert (e.getDate() == date(2021, 11, 30))
        assert (e.getDescription() == "nunta lui Marcel si Eva")


        assert (e.getID() == 1)
        assert (e1.getID() == 2)

    def __test_create_participation(self):
        p = Person(1, 'John', 'Str Zorilor Nr 12')
        p1 = Person(2, 'Tom', 'Str Oilor Nr 12')
        e = Event(1, date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
        e1 = Event(2, date(2023, 11, 30), time(19, 0, 0, 0), "majorat Maria")
        i = Participation(p, e)
        assert (i.getPerson() == p)
        assert (i.getEvent() == e)

        i.setPerson(p1)
        assert (i.getPerson() == p1)
        assert (i.getEvent() == e)

        i.setEvent(e1)
        assert (i.getPerson() == p1)
        assert (i.getEvent() == e1)

    def __test_create_participation_v1(self):
        i = Participation_v1(1, 2)
        assert (i.getPersonID() == 1)
        assert (i.getEventID() == 2)

        i = Participation_v1(2, 7)
        assert (i.getPersonID() == 2)
        assert (i.getEventID() == 7)
