from domain.entities import Person, Event
from repository.events_repo import PersonsRepository, EventsRepository
from domain.validators import PersonValidator, EventValidator

class PersonService:

    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_person(self, name, address):
        """
        adauga persoana
        :param name: numele persoanei
        :type name: str
        :param address: adresa persoanei
        :type address: str
        :return: persoana adaugata in lista
        :rtype: Person
        :raise: ValueError daca persoana este invalida
        """
        person = Person(name, address)
        self.__validator.validate(person)
        self.__repo.store(person)
        return person

    def delete_person(self, id):
        """
        sterge persoana cu id-ul id
        :param id: id-ul persoanei care va fi stearsa
        :type id: int
        :return: persoana stearsa din lista
        :rtype: Person
        """
        deleted_person = self.__repo.search_person_by_id(id)
        self.__repo.delete_person(deleted_person)
        return deleted_person

    def modify_person(self, id, field, value):
        """
        modifica fieldul field al persoanei cu id-ul id cu valoarea value
        :param id: id-ul persoanei care va fi modificata
        :type id: int
        :param field: fieldul care va fi modificata
        :type field: str (name, address)
        :param value: valoarea cu care va fi modificat field-ul field
        :type value: str
        :return: persoana cu datele modificate
        :rtype: Person
        """
        modified_person = self.__repo.search_person_by_id(id)
        #modify_func = eval("self.__repo.modify_person_" + field)
        #modify_func(modified_person, value)
        if field == 'name':
            self.__validator.validate_name(value)
            self.__repo.modify_person_name(modified_person, value)
        else:
            self.__validator.validate_address(value)
            self.__repo.modify_person_address(modified_person, value)
        return modified_person

    def get_all_persons(self):
        return self.__repo.get_all_persons()

def test_add_person():
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

def test_delete_person():
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

class EventService:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_event(self, date, time, description):
        """
        adauga eveniment
        :param date: data evenimentului
        :type date: date
        :param time: ora la care se tine evenimentul
        :type time: time
        :param description: descrierea evenimentului
        :type description: str
        :return event: evenimentul adaugat
        :rtype: Event
        """
        event = Event(date, time, description)
        self.__validator.validate(event)
        self.__repo.store(event)
        return event

    def delete_event(self, id):
        """
        sterge evenimentul cu id-ul id
        :param id: id-ul evenimentului care va fi stearsa
        :type id: int
        :return: evenimentul sters din lista
        :rtype: Event
        """
        deleted_event = self.__repo.search_event_by_id(id)
        self.__repo.delete_event(deleted_event)
        return deleted_event

    def modify_event(self, id, field, value):
        """
        modifica fieldul field al persoanei cu id-ul id cu valoarea value
        :param id: id-ul persoanei care va fi modificata
        :type id: int
        :param field: fieldul care va fi modificata
        :type field: str (name, address)
        :param value: valoarea cu care va fi modificat field-ul field
        :type value: str
        :return: persoana cu datele modificate
        :rtype: Person
        """
        modified_event = self.__repo.search_event_by_id(id)
        #modify_func = eval("self.__repo.modify_person_" + field)
        #modify_func(modified_person, value)

        if field == 'date':
            self.__validator.validate_date(value)
            self.__repo.modify_event_date(modified_event, value)
        elif field == 'time':
            self.__validator.validate_time(value)
            self.__repo.modify_event_time(modified_event, value)
        else:
            self.__validator.validate_description(value)
            self.__repo.modify_event_description(modified_event, value)

        return modified_event

    def get_all_events(self):
        return self.__repo.get_all_events()


def test_add_event():
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")
    events = repo.get_all_events()
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")

    srv.add_event("2022-11-01", "23:00", "descriere 2")
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

    srv.add_event("2023-09-23", "5:00", "descriere 3")
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
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")
    assert (events[1].getID() == 3)
    assert(events[1].getDate() == "2023-09-23")
    assert (events[1].getTime() == "5:00")
    assert (events[1].getDescription() == "descriere 3")

    srv.delete_event(3)
    assert(len(events) == 1)
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-10-10")
    assert (events[0].getTime() == "16:00")
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
    repo = EventsRepository()
    val = EventValidator()
    srv = EventService(repo, val)
    srv.add_event("2021-10-10", "16:00", "descriere 1")

    srv.modify_event(1, "date", "2021-11-11")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-11-11")
    assert (events[0].getTime() == "16:00")
    assert (events[0].getDescription() == "descriere 1")

    srv.modify_event(1, "time", "18:00")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-11-11")
    assert (events[0].getTime() == "18:00")
    assert (events[0].getDescription() == "descriere 1")

    srv.modify_event(1, "description", "descriere noua")
    events = repo.get_all_events()
    assert (events[0].getID() == 1)
    assert(events[0].getDate() == "2021-11-11")
    assert (events[0].getTime() == "18:00")
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
