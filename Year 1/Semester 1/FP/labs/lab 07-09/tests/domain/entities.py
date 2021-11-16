from app.domain.entities import Person, Event, Participation, Participation_v1
from datetime import date, time

def test_create_person():
    p = Person('John', 'Str Zorilor Nr 12')
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

    p1 = Person('Tom', 'Str Oilor Nr 12')
    assert(p.getID() == 1)
    assert(p1.getID() == 2)

def test_create_event():
    e = Event(date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
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

    e2 = Event(date(2023, 11, 30), time(19, 0, 0, 0), "majorat Maria")
    assert (e.getID() == 1)
    assert (e2.getID() == 2)

def test_create_participation():
    p = Person('John', 'Str Zorilor Nr 12')
    np = Person('Tom', 'Str Zorilor Nr 12')
    e = Event(date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
    ne = Event(date(2021, 10, 31), time(19, 0, 0, 0), "botezul Mariei")
    i = Participation(p, e)
    assert (i.getPerson() == p)
    assert (i.getEvent() == e)

    i.setPerson(np)
    assert (i.getPerson() == np)
    assert (i.getEvent() == e)

    i.setEvent(ne)
    assert (i.getPerson() == np)
    assert (i.getEvent() == ne)

def test_create_participation_v1():
    person_repo = Person
    i = Participation_v1(1, 2)
    assert (i.getPersonID() == 1)
    assert (i.getEventID() == 2)

    i = Participation_v1(2, 7)
    assert (i.getPersonID() == 2)
    assert (i.getEventID() == 7)