from domain.entities import Person, Event

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
    pass

def test_get_all_persons():
    pass


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
    pass


def test_get_all_events():
    pass