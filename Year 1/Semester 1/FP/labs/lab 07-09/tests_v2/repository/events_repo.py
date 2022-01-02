from app.domain.entities import Person, Event, Participation_v1
from app.repository.events_repo import PersonsRepository, EventsRepository, ParticipationsRepository


class repo_TEST():
    def run(self):
        self.__test_store_person()
        self.__test_delete_person()
        self.__test_modify_person_address()
        self.__test_store_event()
        self.__test_delete_event()
        self.__test_delete_participation_v1()
        self.__test_modify_event_date()
        self.__test_modify_event_description()
        self.__test_modify_event_time()
        self.__test_modify_person_name()
        self.__test_modify_person_address()
        self.__test_store_participation_v1()
        self.__test_search_person_by_value()
        self.__test_search_event_by_value()

    def __test_store_person(self):
        Person.numberOfPersons = 0
        repo = PersonsRepository()
        p1 = Person(1, "vasile", "str oilor")
        p2 = Person(2, "mariana", "str lalelelor")

        persons = repo.get_all_persons()
        assert(len(persons) == 0)
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

    def __test_delete_person(self):
        Person.numberOfPersons = 0
        repo = PersonsRepository()
        p1 = Person(1,"vasile", "str oilor")
        p2 = Person(2,"mariana", "str lalelelor")
        p3 = Person(3,"tom", "str jupiter")
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

    def __test_modify_person_name(self):
        Person.numberOfPersons = 0
        repo = PersonsRepository()
        p1 = Person(1,"vasile", "str oilor")
        p2 = Person(2,"mariana", "str lalelelor")
        p3 = Person(3,"tom", "str jupiter")
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

    def __test_modify_person_address(self):
        Person.numberOfPersons = 0
        repo = PersonsRepository()
        p1 = Person(1,"vasile", "str oilor")
        p2 = Person(2,"mariana", "str lalelelor")
        p3 = Person(3,"tom", "str jupiter")
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

    def __test_search_person_by_value(self):
        Person.numberOfPersons = 0
        repo = PersonsRepository()
        p1 = Person(1,"vasile", "str oilor")
        p2 = Person(2,"mariana", "str lalelelor")
        p3 = Person(3,"tom", "str jupiter")
        p4 = Person(4,"vasile", "str jupiter")
        repo.store(p1)
        repo.store(p2)
        repo.store(p3)
        repo.store(p4)

        persons = repo.search_person_by_value("id", 1)
        assert(len(persons) == 1)
        assert (persons[0].getID() == 1)
        assert(persons[0].getName() == p1.getName())
        assert (persons[0].getAddress() == p1.getAddress())

        persons = repo.search_person_by_value("name", "vasile")
        assert(len(persons) == 2)
        assert (persons[0].getID() == 1)
        assert(persons[0].getName() == p1.getName())
        assert (persons[0].getAddress() == p1.getAddress())
        assert (persons[1].getID() == 4)
        assert(persons[1].getName() == p4.getName())
        assert (persons[1].getAddress() == p4.getAddress())

        try:
            persons= repo.search_person_by_value("id", 5)
            assert False
        except:
            assert True

        try:
            persons = repo.search_person_by_value("name", "mariana")
            assert False
        except:
            assert True

    def __test_store_event(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
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

    def __test_delete_event(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
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

    def __test_modify_event_date(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
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

    def __test_modify_event_time(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
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

    def __test_modify_event_description(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
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

    def __test_search_event_by_value(self):
        Event.numberOfEvents = 0
        repo = EventsRepository()
        e1 = Event(1,"2021-10-10", "16:00", "descriere 1")
        e2 = Event(2,"2022-11-01", "23:00", "descriere 2")
        e3 = Event(3,"2023-09-23", "5:00", "descriere 3")
        e4 = Event(4,"2021-10-10", "23:00", "descriere 3")
        repo.store(e1)
        repo.store(e2)
        repo.store(e3)
        repo.store(e4)

        events = repo.search_event_by_value("id", 1)
        assert(len(events) == 1)
        assert(events[0].getID() == 1)
        assert(events[0].getDate() == "2021-10-10")
        assert (events[0].getTime() == "16:00")
        assert (events[0].getDescription() == "descriere 1")

        events = repo.search_event_by_value("date", "2021-10-10")
        assert(len(events) == 2)
        assert(events[0].getID() == 1)
        assert(events[0].getDate() == "2021-10-10")
        assert (events[0].getTime() == "16:00")
        assert (events[0].getDescription() == "descriere 1")
        assert(events[1].getID() == 4)
        assert(events[1].getDate() == "2021-10-10")
        assert (events[1].getTime() == "23:00")
        assert (events[1].getDescription() == "descriere 3")

        events = repo.search_event_by_value("time", "23:00")
        assert(len(events) == 2)
        assert(events[0].getID() == 2)
        assert(events[0].getDate() == "2022-11-01")
        assert (events[0].getTime() == "23:00")
        assert (events[0].getDescription() == "descriere 2")
        assert(events[1].getID() == 4)
        assert(events[1].getDate() == "2021-10-10")
        assert (events[1].getTime() == "23:00")
        assert (events[1].getDescription() == "descriere 3")

        try:
            repo.search_event_by_value("id", 10)
            assert False
        except:
            assert True

        try:
            repo.search_event_by_value("date", "10")
            assert False
        except:
            assert True

        try:
            repo.search_event_by_value("time", "19:23")
            assert False
        except:
            assert True

    def __test_store_participation_v1(self):
        repo = ParticipationsRepository()
        p1 = Participation_v1(1,2)
        p2 = Participation_v1(3,4)
        p3 = Participation_v1(1,2)

        participations = repo.get_all_participations()
        assert(len(participations) == 0)

        repo.store_participation(p1)
        participations = repo.get_all_participations()
        assert (len(participations) == 1)
        assert (participations[0].getPersonID() == 1)
        assert (participations[0].getEventID() == 2)

        repo.store_participation(p2)
        participations = repo.get_all_participations()
        assert (len(participations) == 2)
        assert (participations[0].getPersonID() == 1)
        assert (participations[0].getEventID() == 2)
        assert (participations[1].getPersonID() == 3)
        assert (participations[1].getEventID() == 4)

        try:
            repo.store_participation(p3)
            assert False
        except:
            assert True

    def __test_delete_participation_v1(self):
        repo = ParticipationsRepository()
        p1 = Participation_v1(1,2)
        p2 = Participation_v1(3,4)
        p3 = Participation_v1(5,6)
        repo.store_participation(p1)
        repo.store_participation(p2)
        repo.store_participation(p3)

        repo.del_participation(p1)
        participations = repo.get_all_participations()
        assert (len(participations) == 2)
        assert (participations[0].getPersonID() == 3)
        assert (participations[0].getEventID() == 4)
        assert (participations[1].getPersonID() == 5)
        assert (participations[1].getEventID() == 6)

        repo.del_participation(p2)
        participations = repo.get_all_participations()
        assert (len(participations) == 1)
        assert (participations[0].getPersonID() == 5)
        assert (participations[0].getEventID() == 6)

        repo.del_participation(p3)
        participations = repo.get_all_participations()
        assert (len(participations) == 0)

        try:
            repo.del_participation(p1)
            assert False
        except:
            assert True
