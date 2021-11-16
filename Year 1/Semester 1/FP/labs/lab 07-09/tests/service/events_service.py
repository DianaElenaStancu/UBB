from datetime import date, time

from app.domain.entities import Person, Event
from app.domain.validators import PersonValidator, EventValidator
from app.repository.events_repo import PersonsRepository, EventsRepository
from app.service.events_service import PersonService, EventService

def test_add_person():
    Person.numberOfPersons = 0
    repo = PersonsRepository()
    val = PersonValidator()
    srv = PersonService(repo, val)
    srv.add_person("vasile", "str oilor")
    persons = repo.get_all_persons()
    assert(len(persons) == 1)
    assert (len(persons) == 1)
    assert (persons[0].getID() == 1)
    assert (persons[0].getName() == "vasile")
    assert (persons[0].getAddress() == "str oilor")

    srv.add_person("mariana", "str lalelelor")
    persons = repo.get_all_persons()
    assert (len(persons) == 2)
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == "vasile")
    assert (persons[0].getAddress() == "str oilor")
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == "mariana")
    assert (persons[1].getAddress() == "str lalelelor")

    try:
        srv.add_person("", "str jupiter")
        assert False
    except:
        assert True

    persons = repo.get_all_persons()
    assert (len(persons) == 2)

    try:
        srv.add_person("", "")
        assert False
    except:
        assert True

    persons = repo.get_all_persons()
    assert (len(persons) == 2)

    try:
        srv.add_person("tom", "")
        assert False
    except:
        assert True

    persons = repo.get_all_persons()
    assert (len(persons) == 2)

def test_del_person():
    Person.numberOfPersons = 0
    repo = PersonsRepository()
    val = PersonValidator()
    srv = PersonService(repo, val)
    srv.add_person("vasile", "str oilor")
    srv.add_person("tom", "str jupiter")
    srv.add_person("cristi", "str vuvuielelor")
    srv.delete_person(1)

    persons = repo.get_all_persons()
    assert (len(persons) == 2)
    assert (persons[0].getID() == 2)
    assert(persons[0].getName() == "tom")
    assert (persons[0].getAddress() == "str jupiter")
    assert (persons[1].getID() == 3)
    assert(persons[1].getName() == "cristi")
    assert (persons[1].getAddress() == "str vuvuielelor")

    srv.delete_person(2)
    persons = repo.get_all_persons()
    assert (len(persons) == 1)
    assert (persons[0].getID() == 3)
    assert(persons[0].getName() == "cristi")
    assert (persons[0].getAddress() == "str vuvuielelor")

    srv.delete_person(3)
    persons = repo.get_all_persons()
    assert (len(persons) == 0)

    try:
        srv.delete_person(1)
        assert False
    except:
        assert True

    try:
        srv.delete_person(-10)
        assert False
    except:
        assert True

def test_modify_person():
    Person.numberOfPersons = 0
    repo = PersonsRepository()
    val = PersonValidator()
    srv = PersonService(repo, val)
    srv.add_person("vasile", "str oilor")

    srv.modify_person(1, "name", "cristina")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert (persons[0].getName() == "cristina")
    assert (persons[0].getAddress() == "str oilor")

    srv.modify_person(1, "address", "str jupiter")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert (persons[0].getName() == "cristina")
    assert (persons[0].getAddress() == "str jupiter")

    try:
        srv.modify_person(0, "name", "iulia")
        assert False
    except:
        assert True

    try:
        srv.modify_person(1, "name", "")
        assert False
    except:
        assert True

    try:
        srv.modify_person(1, "address", "")
        assert False
    except:
        assert True

def test_search_person():
    Person.numberOfPersons = 0
    repo = PersonsRepository()
    val = PersonValidator()
    srv = PersonService(repo, val)
    srv.add_person("vasile", "str oilor")
    srv.add_person("tom", "str jupiter")
    srv.add_person("cristi", "str vuvuielelor")
    srv.add_person("vasile", "str vuvuielelor")

    persons = srv.search_person("id", 1)
    assert (len(persons) == 1)
    assert (persons[0].getID() == 1)
    assert (persons[0].getName() == "vasile")
    assert (persons[0].getAddress() == "str oilor")

    persons = srv.search_person("name", "vasile")
    assert (len(persons) == 2)
    assert (persons[0].getID() == 1)
    assert (persons[0].getName() == "vasile")
    assert (persons[0].getAddress() == "str oilor")
    assert (persons[1].getID() == 4)
    assert (persons[1].getName() == "vasile")
    assert (persons[1].getAddress() == "str vuvuielelor")

    persons = srv.search_person("address", "str vuvuielelor")
    assert (len(persons) == 2)
    assert (persons[0].getID() == 3)
    assert (persons[0].getName() == "cristi")
    assert (persons[0].getAddress() == "str vuvuielelor")
    assert (persons[1].getID() == 4)
    assert (persons[1].getName() == "vasile")
    assert (persons[1].getAddress() == "str vuvuielelor")

    try:
        srv.search_person("id", 10)
        assert False
    except:
        assert True

    try:
        srv.search_person("name", "")
        assert False
    except:
        assert True

    try:
        srv.search_person("address", "")
        assert False
    except:
        assert True



def test_add_event():
    Event.numberOfEvents = 0
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")
    events = repo.get_all_events()
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,10,10))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")

    srv.add_event("2022-11-01", "23:00", "descriere 2")
    events = repo.get_all_events()
    assert(len(events) == 2)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,10,10))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 2)
    assert(events[1].getDate() == date(2022,11,1))
    assert (events[1].getTime() == time(23,0,0))
    assert (events[1].getDescription() == "descriere 2")

    srv.add_event("2023-09-23", "5:00", "descriere 3")
    events = repo.get_all_events()
    assert(len(events) == 3)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,10,10))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 2)
    assert(events[1].getDate() == date(2022,11,1))
    assert (events[1].getTime() == time(23,0,0))
    assert (events[1].getDescription() == "descriere 2")
    assert (events[2].getID() == 3)
    assert(events[2].getDate() == date(2023,9,23))
    assert (events[2].getTime() == time(5,0,0))
    assert (events[2].getDescription() == "descriere 3")

    try:
        srv.add_event("2023.09-23", "5:00", "descriere 3")
        assert False
    except:
        assert True

    try:
        srv.add_event("2023-09-23", "500", "descriere 3")
        assert False
    except:
        assert True

    try:
        srv.add_event("2023-09-23", "5:00", "")
        assert False
    except:
        assert True

def test_del_event():
    Event.numberOfEvents = 0
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")
    srv.add_event("2022-11-01", "23:00", "descriere 2")
    srv.add_event("2023-09-23", "5:00", "descriere 3")
    events = repo.get_all_events()

    srv.delete_event(2)
    assert(len(events) == 2)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,10,10))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 3)
    assert(events[1].getDate() == date(2023,9,23))
    assert (events[1].getTime() == time(5,0,0))
    assert (events[1].getDescription() == "descriere 3")

    srv.delete_event(3)
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,10,10))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")

    srv.delete_event(1)
    assert(len(events) == 0)


    try:
        srv.delete_event(1)
        assert False
    except:
        assert True

    try:
        srv.delete_event(0)
        assert False
    except:
        assert True

def test_modify_event():
    Event.numberOfEvents = 0
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")

    srv.modify_event(1, "date", "2021-11-11")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,11,11))
    assert (events[0].getTime() == time(16,0,0))
    assert (events[0].getDescription() == "descriere 1")

    srv.modify_event(1, "time", "18:00")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,11,11))
    assert (events[0].getTime() == time(18,0,0))
    assert (events[0].getDescription() == "descriere 1")

    srv.modify_event(1, "description", "descriere noua")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == date(2021,11,11))
    assert (events[0].getTime() == time(18,0,0))
    assert (events[0].getDescription() == "descriere noua")

    try:
        srv.modify_event(1, "description", "")
        assert False
    except:
        assert True

    try:
        srv.modify_event(1, "date", "siahiohda")
        assert False
    except:
        assert True

    try:
        srv.modify_event(1, "date", "2021-13-12")
        assert False
    except:
        assert True

    try:
        srv.modify_event(1, "time", "1600")
        assert False
    except:
        assert True

    try:
        srv.modify_event(1, "time", "25jsoa")
        assert False
    except:
        assert True

def test_search_event():
    Event.numberOfEvents = 0
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")
    srv.add_event("2022-12-09", "15:00", "descriere 2")
    srv.add_event("2023-04-14", "21:00", "descriere 3")
    srv.add_event("2021-10-10", "15:00", "descriere 4")
    events = srv.search_event("id", 1)
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert (events[0].getDate() == date(2021, 10, 10))
    assert (events[0].getTime() == time(16, 0, 0))
    assert (events[0].getDescription() == "descriere 1")

    events = srv.search_event("date", "2021-10-10")
    assert(len(events) == 2)
    assert (events[0].getID() == 1)
    assert (events[0].getDate() == date(2021, 10, 10))
    assert (events[0].getTime() == time(16, 0, 0))
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 4)
    assert (events[1].getDate() == date(2021, 10, 10))
    assert (events[1].getTime() == time(15, 0, 0))
    assert (events[1].getDescription() == "descriere 4")

    events = srv.search_event("time", "15:00")
    assert(len(events) == 2)
    assert (events[0].getID() == 2)
    assert (events[0].getDate() == date(2022,12,9))
    assert (events[0].getTime() == time(15, 0, 0))
    assert (events[0].getDescription() == "descriere 2")
    assert (events[1].getID() == 4)
    assert (events[1].getDate() == date(2021, 10, 10))
    assert (events[1].getTime() == time(15, 0, 0))
    assert (events[1].getDescription() == "descriere 4")

    try:
        srv.search_event("id", 20)
        assert False
    except:
        assert True

    try:
        srv.search_event("date", "202-108")
        assert False
    except:
        assert True

    try:
        srv.search_event("time", 'ddsia')
        assert False
    except:
        assert True

    try:
        srv.search_event("time", "21:21")
        assert False
    except:
        assert True

    try:
        srv.search_event("date", "2002-10-10")
        assert False
    except:
        assert True



