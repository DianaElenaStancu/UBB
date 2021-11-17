
class RepositoryException(Exception):
    pass

class PersonsRepository:
    def __init__(self):
        self.__persons = []

    def store(self, person):
        self.__persons.append(person)

    def search_person_by_value(self, key, value):
        persons = []
        for person in self.__persons:
            if person.getID() == value and key == "id" or person.getName() == value and key == "name" or person.getAddress() == value and key == "address":
                persons.append(person)

        if len(persons) == 0:
            raise RepositoryException("Persoana inexistenta\n")

        return persons

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

    def search_event_by_value(self, key, value):
        events = []
        for event in self.__events:
            if key == "id" and event.getID() == value or event.getDate() == value and key == "date" or event.getTime() == value and key == "time":
                events.append(event)

        if (len(events) == 0):
            raise RepositoryException("Eveniment inexistent\n")

        return events

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
