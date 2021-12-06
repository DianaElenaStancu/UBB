from app.domain.entities import Person, Event
from app.exceptions.exceptions import RepositoryException


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

class PersonsRepositoryFile(PersonsRepository):
    pass


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

class EventsRepositoryFile:
    def __init__(self, filename):
        self.__filename = filename


    def __load_from_file(self):
        """
        incarca evenimentele din fisier
        :return: lista cu evenimente
        :rtype: list of events
        :raises: exception daca nu se poate citi din fisier
        """
        try:
            f = open(self.__filename, 'r')
        except IOError:
            #file doesn't exist
            return []
        events = []
        lines = f.readlines()
        for line in lines:
            date, time, description = [word.strip() for word in line.split(';')]
            event = Event(date, time, description)
            events.append(event)
        f.close()
        return events

    def __save_to_files(self, events):
        """
            Salveaza in fisier o lista de evenimente
            :param shops: lista de evenimente care se salveaza
            :type shops: list of Event
            :return: -; evenimentele sunt salvate in fisier
            :rtype: -
            :raises: Exception daca nu se poate scrie in fisier
        """
        with open(self.__filename, 'w') as f:
            for event in events:
                event_string =  str(event.getDate()) + ';' + str(event.getTime()) + ';' + str(event.getDescription()) + '\n'
                f.write(event_string)



    def store(self, event):
        events = self.__load_from_file()
        events.append(event)
        self.__save_to_files(events)

    def search_event_by_value(self, key, value):
        events = self.__load_from_file()
        events = []
        for event in events:
            if key == "id" and event.getID() == value or event.getDate() == value and key == "date" or event.getTime() == value and key == "time":
                events.append(event)

        if (len(events) == 0):
            raise RepositoryException("Eveniment inexistent\n")

        return events

    def delete_event(self, event):
        events = self.__load_from_file()
        events.remove(event)
        self.__save_to_files(events)

    def modify_event_date(self, event, value):
        events = self.__load_from_file()
        pos = self.events.index(event)
        events[pos].setDate(value)
        self.__save_to_files(events)

    def modify_event_time(self, event, value):
        events = self.__load_from_file()
        pos = events.index(event)
        events[pos].setTime(value)
        self.__save_to_files(events)

    def modify_event_description(self, event, value):
        events = self.__load_from_file()
        pos = events.index(event)
        events[pos].setDescription(value)
        self.__save_to_files(events)

    def get_all_events(self):
        return self.__load_from_file()


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
