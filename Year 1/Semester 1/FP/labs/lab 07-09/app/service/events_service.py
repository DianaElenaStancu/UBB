from datetime import datetime, date, time

from app.domain.entities import Person, Event

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

class EventService:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_event(self, event_date, event_time, description):
        """
        adauga eveniment
        :param event_date: data evenimentului
        :type event_date: date
        :param time: ora la care se tine evenimentul
        :type time: time
        :param description: descrierea evenimentului
        :type description: str
        :return event: evenimentul adaugat
        :rtype: Event
        """
        self.__validator.validate_date(event_date)
        self.__validator.validate_time(event_time)
        self.__validator.validate_description(description)
        format_date = date.fromisoformat(event_date)
        format_time = datetime.strptime(event_time, "%H:%M")
        new_time = time(format_time.hour, format_time.minute)
        event = Event(format_date, new_time, description)
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
            format_date = date.fromisoformat(value)
            self.__repo.modify_event_date(modified_event, format_date)
        elif field == 'time':
            self.__validator.validate_time(value)
            format_time = datetime.strptime(value, "%H:%M")
            new_time = time(format_time.hour, format_time.minute)
            self.__repo.modify_event_time(modified_event, new_time)
        else:
            self.__validator.validate_description(value)
            self.__repo.modify_event_description(modified_event, value)

        return modified_event

    def get_all_events(self):
        return self.__repo.get_all_events()
