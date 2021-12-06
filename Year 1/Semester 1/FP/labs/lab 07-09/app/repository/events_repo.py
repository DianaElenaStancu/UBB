from datetime import datetime, date, time

from app.domain.entities import Person, Event, Participation_v1
from app.exceptions.exceptions import RepositoryException


class PersonsRepository:
    def __init__(self):
        self._persons = []

    def store(self, person):
        self._persons.append(person)

    def search_person_by_value(self, key, value):
        persons = []
        for person in self._persons:
            if person.getID() == value and key == "id" or person.getName() == value and key == "name" or person.getAddress() == value and key == "address":
                persons.append(person)

        if len(persons) == 0:
            raise RepositoryException("Persoana inexistenta\n")

        return persons

    def delete_person(self, person):
       self._persons.remove(person)

    def modify_person_name(self, person, value):
        pos = self._persons.index(person)
        self._persons[pos].setName(value)

    def modify_person_address(self, person, value):
        pos = self._persons.index(person)
        self._persons[pos].setAddress(value)

    def remove_all(self):
        self._persons.clear()

    def get_all_persons(self):
        return self._persons

class PersonsRepositoryFile(PersonsRepository):
    def __init__(self, filename):
        """
        initializam repository-ul
        filename - string, file patg
        post: persoane sunt incarcate din fisier
        """
        PersonsRepository.__init__(self)
        self.__filename = filename
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            PersonsRepository.remove_all(self)
            for line in f:
                line = line.strip()
                if line == "":
                    continue
                attrs = line.split(";")
                id = int(attrs[0])
                name = attrs[1]
                address = attrs[2]
                person = Person(id, name, address)
                PersonsRepository.store(self, person)

    def __saveToFile(self, persons):
        with open(self.__filename, "w") as f:
            for person in persons:
                f.write(person.to_string())

    def store(self, person):
        PersonsRepository.store(self, person)
        persons = PersonsRepository.get_all_persons(self)
        self.__saveToFile(persons)

    def delete_person(self, person):
        PersonsRepository.delete_person(self, person)
        persons = PersonsRepository.get_all_persons(self)
        self.__saveToFile(persons)

    def search_person_by_value(self, key, value):
        self.__loadFromFile()
        return PersonsRepository.search_person_by_value(self, key, value)

    def modify_person_name(self, person, value):
        self.__loadFromFile()
        PersonsRepository.modify_person_name(self, person, value)
        self.__saveToFile(self._persons)

    def modify_person_address(self, person, value):
        self.__loadFromFile()
        PersonsRepository.modify_person_address(self, person, value)
        self.__saveToFile(self._persons)


class EventsRepository():
    def __init__(self):
        self._events = []

    def store(self, event):
        self._events.append(event)

    def search_event_by_value(self, key, value):
        events = []
        for event in self._events:
            if key == "id" and event.getID() == value or event.getDate() == value and key == "date" or event.getTime() == value and key == "time":
                events.append(event)

        if (len(events) == 0):
            raise RepositoryException("Eveniment inexistent\n")

        return events

    def delete_event(self, event):
       self._events.remove(event)

    def modify_event_date(self, event, value):
        pos = self._events.index(event)
        self._events[pos].setDate(value)

    def modify_event_time(self, event, value):
        pos = self._events.index(event)
        self._events[pos].setTime(value)

    def modify_event_description(self, event, value):
        pos = self._events.index(event)
        self._events[pos].setDescription(value)

    def remove_all(self):
        self._events = []

    def get_all_events(self):
        return self._events

class EventsRepositoryFile(EventsRepository):
    def __init__(self, filename):
        EventsRepository.__init__(self)
        self.__filename = filename
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            EventsRepository.remove_all(self)
            for line in f:
                line = line.strip()
                if line == "":
                    continue
                attrs = line.split(";")
                id = int(attrs[0])
                event_date = attrs[1]
                event_time = attrs[2]
                description = attrs[3]
                format_date = date.fromisoformat(event_date)
                format_time = datetime.strptime(event_time, "%H:%M")
                new_time = time(format_time.hour, format_time.minute)
                event = Event(id, format_date, new_time, description)
                EventsRepository.store(self, event)


    def __saveToFile(self, events):
        with open(self.__filename, "w") as f:
            for event in events:
                f.write(event.to_string())

    def store(self, event):
        EventsRepository.store(self, event)
        events = EventsRepository.get_all_events(self)
        self.__saveToFile(events)

    def search_event_by_value(self, key, value):
        self.__loadFromFile()
        return EventsRepository.search_event_by_value(self, key, value)

    def delete_event(self, event):
        EventsRepository.delete_event(self, event)
        events = EventsRepository.get_all_events(self)
        self.__saveToFile(events)

    def modify_event_date(self, event, value):
        self.__loadFromFile()
        EventsRepository.modify_event_date(self, event, value)
        self.__saveToFile(self._events)

    def modify_event_time(self, event, value):
        self.__loadFromFile()
        EventsRepository.modify_event_time(self, event, value)
        self.__saveToFile(self._events)

    def modify_event_description(self, event, value):
        self.__loadFromFile()
        EventsRepository.modify_event_description(self, event, value)
        self.__saveToFile(self._events)


class ParticipationsRepository:
    def __init__(self):
        self.__participations = []

    def get_all_participations(self):
        return self.__participations

    def store_participation(self, participation):
        if participation in self.__participations:
            raise RepositoryException("Participare existenta\n")
        self.__participations.append(participation)

    def del_participation(self, participation):
        if participation not in self.__participations:
            raise RepositoryException("Participare inexistenta\n")
        self.__participations.remove(participation)

    def search_participation_by_person_id(self, person_id):
        """cauta participarile dupa id-ul persoanei person_id"""
        participations_list = []
        for participation in self.__participations:
            if participation.getPersonID() == person_id:
                participations_list.append(participation)

        if(len(participations_list) == 0):
            raise RepositoryException("Nu exista evenimente la care participa persoana cu id-ul dat.")

        return participations_list

class ParticipationsRepositoryFile(ParticipationsRepository):
    def __init__(self, filename):
        ParticipationsRepository.__init__(self)
        self.__filename = filename
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            EventsRepository.remove_all(self)
            for line in f:
                line = line.strip()
                if line == "":
                    continue
                attrs = line.split(";")
                id1 = int(attrs[0])
                id2 = int(attrs[1])
                participation = Participation_v1(id1,id2)
                ParticipationsRepository.store_participation(self, participation)


    def __saveToFile(self, participations):
        with open(self.__filename, "w") as f:
            for participation in participations:
                f.write(participation.to_string())

    def store_participation(self, participation):
        ParticipationsRepository.store_participation(self, participation)
        participations = ParticipationsRepository.get_all_participations(self)
        self.__saveToFile(participations)

    def del_participation(self, participation):
        ParticipationsRepository.del_participation(self, participation)
        participations = ParticipationsRepository.get_all_participations(self)
        self.__saveToFile(participations)

    def search_participation_by_person_id(self, person_id):
        self.__loadFromFile()
        return ParticipationsRepository.search_participation_by_person_id(self, person_id)
