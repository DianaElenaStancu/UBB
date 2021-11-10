from app.domain.entities import Person, Event
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