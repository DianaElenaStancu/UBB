import names
from random_address import real_random_address
import random
from random import randint
from datetime import datetime, date, time

from app.domain.entities import Person, Event, Participation, Participation_v1

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
        self.__validator.validate_name(name)
        self.__validator.validate_address(address)
        person = Person(name, address)
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
        person_list_with_id = self.__repo.search_person_by_value("id", id)
        deleted_person = person_list_with_id[0]
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
        person_list = self.__repo.search_person_by_value("id", id)
        modified_person = person_list[0]
        #modify_func = eval("self.__repo.modify_person_" + field)
        #modify_func(modified_person, value)
        if field == 'name':
            self.__validator.validate_name(value)
            self.__repo.modify_person_name(modified_person, value)
        else:
            self.__validator.validate_address(value)
            self.__repo.modify_person_address(modified_person, value)
        return modified_person

    def search_person(self, field, value):
        """cauta persoana dupa id"""
        searched_persons = self.__repo.search_person_by_value(field, value)
        return searched_persons

    def generate_persons(self, nr):
        """genereaza nr persoane"""
        while nr:
            name = names.get_last_name()
            address = real_random_address()["address1"]
            person = Person(name, address)
            self.__repo.store(person)
            nr -= 1

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
        event_list = self.__repo.search_event_by_value("id", id)
        deleted_event = event_list[0]
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
        event_list = self.__repo.search_event_by_value("id", id)
        modified_event = event_list[0]
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

    def search_event(self, field, value):
        """cauta un eveniment dupa un camp dat"""
        if field == "id":
            searched_events = self.__repo.search_event_by_value(field, value)
        elif field == "date":
            self.__validator.validate_date(value)
            format_date = date.fromisoformat(value)
            searched_events = self.__repo.search_event_by_value(field, format_date)
        else:
            self.__validator.validate_time(value)
            format_time = datetime.strptime(value, "%H:%M")
            new_time = time(format_time.hour, format_time.minute)
            searched_events = self.__repo.search_event_by_value(field, new_time)
        return searched_events

    def generate_events(self, nr):
        """genereaza un numar nr de evenimente"""
        while nr:
            year = randint(2021, 2100)
            month = randint(1, 12)
            day = randint(1, 28)
            hour = randint(0, 23)
            minutes = randint(0, 59)
            date_value = date(year, month, day)
            time_value = time(hour, minutes, 0)
            description = random.choice(["nunta", "bal", "majorat", "aniversare", "botez"])
            event = Event(date_value, time_value, description)
            self.__repo.store(event)
            nr -= 1

    def get_all_events(self):
        return self.__repo.get_all_events()

class ParticipationService:
    def __init__(self, persons_repo, events_repo, participations_repo):
        self.__persons_repo = persons_repo
        self.__events_repo = events_repo
        self.__participations_repo = participations_repo

    def get_all_participations(self):
        return self.__participations_repo.get_all_participations()

    def add_participation(self, person_id, event_id):
        """
        Persoana cu id-ul person_id participa la evenimentul cu id-ul event_id
        :param person_id: id-ul persoanei
        :type person_id: int
        :param event_id: id-ul evenimentului
        :type event_id: int
        :return: persoana si evenimentul
        :rtype: list of Person and Event
        """
        #for Participation(v0)
        #person_list = self.__persons_repo.search_person_by_value("id", person_id)
        #event_list = self.__events_repo.search_event_by_value("id", event_id)
        #person = person_list[0]
        #event = event_list[0]
        participation = Participation_v1(person_id, event_id)
        self.__persons_repo.search_person_by_value("id", person_id)
        self.__events_repo.search_event_by_value("id", event_id)
        self.__participations_repo.store_participation(participation)
        #return [person, event]

    def del_participation(self, person_id, event_id):
        """
        Eliminam participarea persoanei cu id-ul person_id la evenimentul cu id-ul event-id
        :param person_id: id-ul persoanei
        :type person_id: int
        :param event_id: id-ul evenimentului
        :type event_id: int
        :return: persoana si evenimentul
        :rtype: list of Person and Event
        """
        # for Participation(v0)
        #person_list = self.__persons_repo.search_person_by_value("id", person_id)
        #event_list = self.__events_repo.search_event_by_value("id", event_id)
        #person = person_list[0]
        #event = event_list[0]
        self.__persons_repo.search_person_by_value("id", person_id)
        self.__events_repo.search_event_by_value("id", event_id)
        participation = Participation_v1(person_id, event_id)
        self.__participations_repo.del_participation(participation)
        #return [person, event]

