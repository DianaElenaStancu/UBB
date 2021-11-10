
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
        raise RepositoryException("Persoana inexistenta\n")

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
