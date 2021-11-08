from domain.entities import Person, Event

class RepositoryException(Exception):
    pass

class PersonsRepository:
    def __init__(self):
        self.__persons = []

    def store(self, person):
        self.__persons.append(person)

    def search_person_by_id(self, id):
        for person in self.__persons:
            if person.getID() == id:
                return person
        raise ValueError("Persoana inexistenta\n")

    def delete_person(self, person):
       self.__persons.remove(person)

    def modify_person_name(self, person, value):
        pos = self.__persons.index(person)
        self.__persons[pos].setName(value)

    def modify_person_address(self, person, value):
        pos = self.__persons.index(person)
        self.__persons[pos].setAddress(value)

    def get_all_persons(self):
        return self.__persons

def test_store_person():
    repo = PersonsRepository()
    p1 = Person("vasile", "str oilor")
    p2 = Person("mariana", "str lalelelor")

    assert(len(repo.get_all_persons()) == 0)

    repo.store(p1)
    persons = repo.get_all_persons()
    assert(len(persons) == 1)
    assert(persons[0].getID() == 1)
    assert(persons[0].getName() == p1.getName())
    assert (persons[0].getAddress() == p1.getAddress())

    repo.store(p2)
    persons = repo.get_all_persons()
    assert (len(persons) == 2)
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == p1.getName())
    assert (persons[0].getAddress() == p1.getAddress())
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == p2.getName())
    assert (persons[1].getAddress() == p2.getAddress())

def test_delete_person():
    repo = PersonsRepository()
    p1 = Person("vasile", "str oilor")
    p2 = Person("mariana", "str lalelelor")
    p3 = Person("tom", "str jupiter")
    repo.store(p1)
    repo.store(p2)
    repo.store(p3)

    repo.delete_person(p1)
    persons = repo.get_all_persons()
    assert (len(persons) == 2)
    assert (persons[0].getID() == 2)
    assert(persons[0].getName() == p2.getName())
    assert (persons[0].getAddress() == p2.getAddress())
    assert (persons[1].getID() == 3)
    assert(persons[1].getName() == p3.getName())
    assert (persons[1].getAddress() == p3.getAddress())

    repo.delete_person(p2)
    persons = repo.get_all_persons()
    assert (len(persons) == 1)
    assert (persons[0].getID() == 3)
    assert(persons[0].getName() == p3.getName())
    assert (persons[0].getAddress() == p3.getAddress())

    repo.delete_person(p3)
    persons = repo.get_all_persons()
    assert (len(persons) == 0)

def test_modify_person_name():
    repo = PersonsRepository()
    p1 = Person("vasile", "str oilor")
    p2 = Person("mariana", "str lalelelor")
    p3 = Person("tom", "str jupiter")
    repo.store(p1)
    repo.store(p2)
    repo.store(p3)

    repo.modify_person_name(p1, "clara")
    persons = repo.get_all_persons()
    assert (len(persons) == 3)
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == "clara")
    assert (persons[0].getAddress() == p1.getAddress())
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == p2.getName())
    assert (persons[1].getAddress() == p2.getAddress())
    assert(persons[2].getName() == p3.getName())
    assert (persons[2].getAddress() == p3.getAddress())

    repo.modify_person_name(p2, "paul")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == "clara")
    assert (persons[0].getAddress() == p1.getAddress())
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == "paul")
    assert (persons[1].getAddress() == p2.getAddress())
    assert (persons[2].getID() == 3)
    assert(persons[2].getName() == p3.getName())
    assert (persons[2].getAddress() == p3.getAddress())

    repo.modify_person_name(p3, "ana")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == "clara")
    assert (persons[0].getAddress() == p1.getAddress())
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == "paul")
    assert (persons[1].getAddress() == p2.getAddress())
    assert (persons[2].getID() == 3)
    assert(persons[2].getName() == "ana")
    assert (persons[2].getAddress() == p3.getAddress())

def test_modify_person_address():
    repo = PersonsRepository()
    p1 = Person("vasile", "str oilor")
    p2 = Person("mariana", "str lalelelor")
    p3 = Person("tom", "str jupiter")
    repo.store(p1)
    repo.store(p2)
    repo.store(p3)

    repo.modify_person_address(p1, "str mercur")
    persons = repo.get_all_persons()
    assert (len(persons) == 3)
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == p1.getName())
    assert (persons[0].getAddress() == "str mercur")
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == p2.getName())
    assert (persons[1].getAddress() == p2.getAddress())
    assert (persons[2].getID() == 3)
    assert(persons[2].getName() == p3.getName())
    assert (persons[2].getAddress() == p3.getAddress())

    repo.modify_person_address(p2, "str unirii")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == p1.getName())
    assert (persons[0].getAddress() == "str mercur")
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == p2.getName())
    assert (persons[1].getAddress() == "str unirii")
    assert (persons[2].getID() == 3)
    assert(persons[2].getName() == p3.getName())
    assert (persons[2].getAddress() == p3.getAddress())

    repo.modify_person_address(p3, "str victoriei")
    persons = repo.get_all_persons()
    assert (persons[0].getID() == 1)
    assert(persons[0].getName() == p1.getName())
    assert (persons[0].getAddress() == "str mercur")
    assert (persons[1].getID() == 2)
    assert(persons[1].getName() == p2.getName())
    assert (persons[1].getAddress() == "str unirii")
    assert (persons[2].getID() == 3)
    assert(persons[2].getName() == p3.getName())
    assert (persons[2].getAddress() == "str victoriei")

class EventsRepository():
    def __init__(self):
        self.__events = []

    def store(self, event):
        self.__events.append(event)

    def search_event_by_id(self, id):
        for event in self.__events:
            if event.getID() == id:
                return event
        raise ValueError("Eveniment inexistent\n")

    def delete_event(self, event):
       self.__events.remove(event)

    def modify_event_date(self, event, value):
        pos = self.__events.index(event)
        self.__events[pos].setDate(value)

    def modify_event_time(self, event, value):
        pos = self.__events.index(event)
        self.__events[pos].setTime(value)

    def modify_event_description(self, event, value):
        pos = self.__events.index(event)
        self.__events[pos].setDescription(value)

    def get_all_events(self):
        return self.__events

def test_store():
    repo = EventsRepository()
    e1 = Event("2021-10-10", "16:00", "descriere 1")
    e2 = Event("2022-11-01", "23:00", "descriere 2")
    e3 = Event("2023-09-23", "5:00", "descriere 3")
    events = repo.get_all_events()
    assert(len(events) == 0)

    repo.store(e1)
    events = repo.get_all_events()
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")

    repo.store(e2)
    events = repo.get_all_events()
    assert(len(events) == 2)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")

    repo.store(e3)
    events = repo.get_all_events()
    assert(len(events) == 3)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert (events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

def test_delete_event():
    repo = EventsRepository()
    e1 = Event("2021-10-10", "16:00", "descriere 1")
    e2 = Event("2022-11-01", "23:00", "descriere 2")
    e3 = Event("2023-09-23", "5:00", "descriere 3")
    repo.store(e1)
    repo.store(e2)
    repo.store(e3)

    repo.delete_event(e1)
    events = repo.get_all_events()
    assert(len(events) == 2)
    assert(events[0].getID() == 2)
    assert(events[0].getDate() == "2022-11-01")
    assert (events[0].getTime() == "23:00")
    assert (events[0].getDescription() == "descriere 2")
    assert(events[1].getID() == 3)
    assert(events[1].getDate() == "2023-09-23")
    assert (events[1].getTime() == "5:00")
    assert (events[1].getDescription() == "descriere 3")

    repo.delete_event(e2)
    events = repo.get_all_events()
    assert(len(events) == 1)
    assert(events[0].getID() == 3)
    assert(events[0].getDate() == "2023-09-23")
    assert (events[0].getTime() == "5:00")
    assert (events[0].getDescription() == "descriere 3")

    repo.delete_event(e3)
    events = repo.get_all_events()
    assert(len(events) == 0)

def test_modify_event_date():
    repo = EventsRepository()
    e1 = Event("2021-10-10", "16:00", "descriere 1")
    e2 = Event("2022-11-01", "23:00", "descriere 2")
    e3 = Event("2023-09-23", "5:00", "descriere 3")
    repo.store(e1)
    repo.store(e2)
    repo.store(e3)

    repo.modify_event_date(e1, "2019-03-04")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2019-03-04")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_date(e2, "2089-12-12")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2019-03-04")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2089-12-12")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_date(e3, "2004-11-01")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2019-03-04")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2089-12-12")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2004-11-01")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

def test_modify_event_time():
    repo = EventsRepository()
    e1 = Event("2021-10-10", "16:00", "descriere 1")
    e2 = Event("2022-11-01", "23:00", "descriere 2")
    e3 = Event("2023-09-23", "5:00", "descriere 3")
    repo.store(e1)
    repo.store(e2)
    repo.store(e3)

    repo.modify_event_time(e1, "23:00")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "23:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_time(e2, "17:00")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "23:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "17:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_time(e3, "20:00")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "23:00")
    assert (events[0].getDescription() == "descriere 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "17:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "20:00")
    assert (events[2].getDescription() == "descriere 3")

def test_modify_event_description():
    repo = EventsRepository()
    e1 = Event("2021-10-10", "16:00", "descriere 1")
    e2 = Event("2022-11-01", "23:00", "descriere 2")
    e3 = Event("2023-09-23", "5:00", "descriere 3")
    repo.store(e1)
    repo.store(e2)
    repo.store(e3)

    repo.modify_event_description(e1, "descriere noua 1")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere noua 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_description(e2, "descriere noua 2")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere noua 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere noua 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere 3")

    repo.modify_event_description(e3, "descriere noua 3")
    events = repo.get_all_events()
    assert(events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere noua 1")
    assert(events[1].getID() == 2)
    assert(events[1].getDate() == "2022-11-01")
    assert (events[1].getTime() == "23:00")
    assert (events[1].getDescription() == "descriere noua 2")
    assert(events[2].getID() == 3)
    assert(events[2].getDate() == "2023-09-23")
    assert (events[2].getTime() == "5:00")
    assert (events[2].getDescription() == "descriere noua 3")