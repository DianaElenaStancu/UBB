from datetime import date, time

from app.domain.entities import Person, Event, Participation_v1
from app.domain.validators import PersonValidator, EventValidator
from app.repository.events_repo import PersonsRepository, EventsRepository, ParticipationsRepository
from app.service.events_service import PersonService, EventService, ParticipationService
from app.utils.id_generator import IdGenerator
import unittest

class testSrv(unittest.TestCase):
    def setUp(self) -> None:
        self.__personRepo = PersonsRepository()
        self.__personVal = PersonValidator()
        self.__gen = IdGenerator("../../tests_v2/utils/id_history.txt")
        self.__personSrv = PersonService(self.__personRepo, self.__personVal, self.__gen)
        self.__eventRepo = EventsRepository()
        self.__eventVal = EventValidator()
        self.__eventSrv = EventService( self.__eventRepo,self.__eventVal, self.__gen)
        self.__participationRepo = ParticipationsRepository()
        self.__participationSrv = ParticipationService(self.__personRepo, self.__eventRepo, self.__participationRepo)

    def test_add_person(self):
        self.__gen.reset_file()
        self.__personSrv.add_person("vasile", "str oilor")
        persons = self.__personRepo.get_all_persons()
        assert(len(persons) == 1)
        assert (len(persons) == 1)
        assert (persons[0].getID() == 1)
        assert (persons[0].getName() == "vasile")
        assert (persons[0].getAddress() == "str oilor")

        self.__personSrv.add_person("mariana", "str lalelelor")
        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 2)
        assert (persons[0].getID() == 1)
        assert(persons[0].getName() == "vasile")
        assert (persons[0].getAddress() == "str oilor")
        assert (persons[1].getID() == 2)
        assert(persons[1].getName() == "mariana")
        assert (persons[1].getAddress() == "str lalelelor")

        try:
            self.__personSrv.add_person("", "str jupiter")
            assert False
        except:
            assert True

        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 2)

        try:
            self.__personSrv.add_person("", "")
            assert False
        except:
            assert True

        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 2)

        try:
            self.__personSrv.add_person("tom", "")
            assert False
        except:
            assert True

        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 2)

    def test_del_person(self):
        self.__gen.reset_file()
        self.__personSrv.add_person("vasile", "str oilor")
        self.__personSrv.add_person("tom", "str jupiter")
        self.__personSrv.add_person("cristi", "str vuvuielelor")
        self.__personSrv.delete_person(1)

        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 2)
        assert (persons[0].getID() == 2)
        assert(persons[0].getName() == "tom")
        assert (persons[0].getAddress() == "str jupiter")
        assert (persons[1].getID() == 3)
        assert(persons[1].getName() == "cristi")
        assert (persons[1].getAddress() == "str vuvuielelor")

        self.__personSrv.delete_person(2)
        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 1)
        assert (persons[0].getID() == 3)
        assert(persons[0].getName() == "cristi")
        assert (persons[0].getAddress() == "str vuvuielelor")

        self.__personSrv.delete_person(3)
        persons = self.__personRepo.get_all_persons()
        assert (len(persons) == 0)

        try:
            self.__personSrv.delete_person(1)
            assert False
        except:
            assert True

        try:
            self.__personSrv.delete_person(-10)
            assert False
        except:
            assert True

    def test_modify_person(self):
        self.__gen.reset_file()
        self.__personSrv.add_person("vasile", "str oilor")

        self.__personSrv.modify_person(1, "name", "cristina")
        persons = self.__personRepo.get_all_persons()
        assert (persons[0].getID() == 1)
        assert (persons[0].getName() == "cristina")
        assert (persons[0].getAddress() == "str oilor")

        self.__personSrv.modify_person(1, "address", "str jupiter")
        persons = self.__personRepo.get_all_persons()
        assert (persons[0].getID() == 1)
        assert (persons[0].getName() == "cristina")
        assert (persons[0].getAddress() == "str jupiter")

        try:
            self.__personSrv.modify_person(0, "name", "iulia")
            assert False
        except:
            assert True

        try:
            self.__personSrv.modify_person(1, "name", "")
            assert False
        except:
            assert True

        try:
            self.__personSrv.modify_person(1, "address", "")
            assert False
        except:
            assert True

    def test_search_person(self):
        self.__gen.reset_file()
        self.__personSrv.add_person("vasile", "str oilor")
        self.__personSrv.add_person("tom", "str jupiter")
        self.__personSrv.add_person("cristi", "str vuvuielelor")
        self.__personSrv.add_person("vasile", "str vuvuielelor")

        persons = self.__personSrv.search_person("id", 1)
        assert (len(persons) == 1)
        assert (persons[0].getID() == 1)
        assert (persons[0].getName() == "vasile")
        assert (persons[0].getAddress() == "str oilor")

        persons = self.__personSrv.search_person("name", "vasile")
        assert (len(persons) == 2)
        assert (persons[0].getID() == 1)
        assert (persons[0].getName() == "vasile")
        assert (persons[0].getAddress() == "str oilor")
        assert (persons[1].getID() == 4)
        assert (persons[1].getName() == "vasile")
        assert (persons[1].getAddress() == "str vuvuielelor")

        persons = self.__personSrv.search_person("address", "str vuvuielelor")
        assert (len(persons) == 2)
        assert (persons[0].getID() == 3)
        assert (persons[0].getName() == "cristi")
        assert (persons[0].getAddress() == "str vuvuielelor")
        assert (persons[1].getID() == 4)
        assert (persons[1].getName() == "vasile")
        assert (persons[1].getAddress() == "str vuvuielelor")

        try:
            self.__personSrv.search_person("id", 10)
            assert False
        except:
            assert True

        try:
            self.__personSrv.search_person("name", "")
            assert False
        except:
            assert True

        try:
            self.__personSrv.search_person("address", "")
            assert False
        except:
            assert True

    def test_add_event(self):
        self.__gen.reset_file()
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")
        events = self.__eventRepo.get_all_events()
        assert(len(events) == 1)
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,10,10))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")

        self.__eventSrv.add_event("2022-11-01", "23:00", "descriere 2")
        events = self.__eventRepo.get_all_events()
        assert(len(events) == 2)
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,10,10))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")
        assert (events[1].getID() == 2)
        assert(events[1].getDate() == date(2022,11,1))
        assert (events[1].getTime() == time(23,0,0))
        assert (events[1].getDescription() == "descriere 2")

        self.__eventSrv.add_event("2023-09-23", "5:00", "descriere 3")
        events = self.__eventRepo.get_all_events()
        assert(len(events) == 3)
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,10,10))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")
        assert (events[1].getID() == 2)
        assert(events[1].getDate() == date(2022,11,1))
        assert (events[1].getTime() == time(23,0,0))
        assert (events[1].getDescription() == "descriere 2")
        assert (events[2].getID() == 3)
        assert(events[2].getDate() == date(2023,9,23))
        assert (events[2].getTime() == time(5,0,0))
        assert (events[2].getDescription() == "descriere 3")

        try:
            self.__eventSrv.add_event("2023.09-23", "5:00", "descriere 3")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.add_event("2023-09-23", "500", "descriere 3")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.add_event("2023-09-23", "5:00", "")
            assert False
        except:
            assert True

    def test_del_event(self):
        self.__gen.reset_file()
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")
        self.__eventSrv.add_event("2022-11-01", "23:00", "descriere 2")
        self.__eventSrv.add_event("2023-09-23", "5:00", "descriere 3")
        events = self.__eventRepo.get_all_events()

        self.__eventSrv.delete_event(2)
        assert(len(events) == 2)
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,10,10))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")
        assert (events[1].getID() == 3)
        assert(events[1].getDate() == date(2023,9,23))
        assert (events[1].getTime() == time(5,0,0))
        assert (events[1].getDescription() == "descriere 3")

        self.__eventSrv.delete_event(3)
        assert(len(events) == 1)
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,10,10))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")

        self.__eventSrv.delete_event(1)
        assert(len(events) == 0)


        try:
            self.__eventSrv.delete_event(1)
            assert False
        except:
            assert True

        try:
            self.__eventSrv.delete_event(0)
            assert False
        except:
            assert True

    def test_modify_event(self):
        self.__gen.reset_file()
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")

        self.__eventSrv.modify_event(1, "date", "2021-11-11")
        events = self.__eventRepo.get_all_events()
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,11,11))
        assert (events[0].getTime() == time(16,0,0))
        assert (events[0].getDescription() == "descriere 1")

        self.__eventSrv.modify_event(1, "time", "18:00")
        events = self.__eventRepo.get_all_events()
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,11,11))
        assert (events[0].getTime() == time(18,0,0))
        assert (events[0].getDescription() == "descriere 1")

        self.__eventSrv.modify_event(1, "description", "descriere noua")
        events = self.__eventRepo.get_all_events()
        assert (events[0].getID() == 1)
        assert(events[0].getDate() == date(2021,11,11))
        assert (events[0].getTime() == time(18,0,0))
        assert (events[0].getDescription() == "descriere noua")

        try:
            self.__eventSrv.modify_event(1, "description", "")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.modify_event(1, "date", "siahiohda")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.modify_event(1, "date", "2021-13-12")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.modify_event(1, "time", "1600")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.modify_event(1, "time", "25jsoa")
            assert False
        except:
            assert True

    def test_search_event(self):
        self.__gen.reset_file()
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")
        self.__eventSrv.add_event("2022-12-09", "15:00", "descriere 2")
        self.__eventSrv.add_event("2023-04-14", "21:00", "descriere 3")
        self.__eventSrv.add_event("2021-10-10", "15:00", "descriere 4")
        events = self.__eventSrv.search_event("id", 1)
        assert(len(events) == 1)
        assert (events[0].getID() == 1)
        assert (events[0].getDate() == date(2021, 10, 10))
        assert (events[0].getTime() == time(16, 0, 0))
        assert (events[0].getDescription() == "descriere 1")

        events = self.__eventSrv.search_event("date", "2021-10-10")
        assert(len(events) == 2)
        assert (events[0].getID() == 1)
        assert (events[0].getDate() == date(2021, 10, 10))
        assert (events[0].getTime() == time(16, 0, 0))
        assert (events[0].getDescription() == "descriere 1")
        assert (events[1].getID() == 4)
        assert (events[1].getDate() == date(2021, 10, 10))
        assert (events[1].getTime() == time(15, 0, 0))
        assert (events[1].getDescription() == "descriere 4")

        events = self.__eventSrv.search_event("time", "15:00")
        assert(len(events) == 2)
        assert (events[0].getID() == 2)
        assert (events[0].getDate() == date(2022,12,9))
        assert (events[0].getTime() == time(15, 0, 0))
        assert (events[0].getDescription() == "descriere 2")
        assert (events[1].getID() == 4)
        assert (events[1].getDate() == date(2021, 10, 10))
        assert (events[1].getTime() == time(15, 0, 0))
        assert (events[1].getDescription() == "descriere 4")

        try:
            self.__eventSrv.search_event("id", 20)
            assert False
        except:
            assert True

        try:
            self.__eventSrv.search_event("date", "202-108")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.search_event("time", 'ddsia')
            assert False
        except:
            assert True

        try:
            self.__eventSrv.search_event("time", "21:21")
            assert False
        except:
            assert True

        try:
            self.__eventSrv.search_event("date", "2002-10-10")
            assert False
        except:
            assert True

    def __test_add_participation_v1(self):

        self.__gen.reset_file()
        self.__personSrv.add_person("vasile", "str oilor")
        self.__personSrv.add_person("tom", "str jupiter")
        self.__personSrv.add_person("cristi", "str vuvuielelor")
        self.__personSrv.add_person("vasile", "str vuvuielelor")
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")
        self.__eventSrv.add_event("2022-12-09", "15:00", "descriere 2")
        self.__eventSrv.add_event("2023-04-14", "21:00", "descriere 3")
        self.__eventSrv.add_event("2021-10-10", "15:00", "descriere 4")

        participations = self.__participationSrv.get_all_participations()
        assert(len(participations) == 0)

        self.__participationSrv.add_participation(1, 2)
        participations = self.__participationSrv.get_all_participations()
        assert(len(participations) == 1)
        assert (participations[0].getPersonID() == 1)
        assert (participations[0].getEventID() == 2)

        self.__participationSrv.add_participation(3, 4)
        assert(len(participations) == 2)
        assert (participations[0].getPersonID() == 1)
        assert (participations[0].getEventID() == 2)
        assert (participations[1].getPersonID() == 3)
        assert (participations[1].getEventID() == 4)

        try:
            self.__participationSrv.add_participation(1, 2)
            assert False
        except:
            assert True

    def __test_del_participation_v1(self):
        self.__gen.reset_file()

        self.__personSrv.add_person("vasile", "str oilor")
        self.__personSrv.add_person("tom", "str jupiter")
        self.__personSrv.add_person("cristi", "str vuvuielelor")
        self.__personSrv.add_person("vasile", "str vuvuielelor")
        self.__eventSrv.add_event("2021-10-10", "16:00", "descriere 1")
        self.__eventSrv.add_event("2022-12-09", "15:00", "descriere 2")
        self.__eventSrv.add_event("2023-04-14", "21:00", "descriere 3")
        self.__eventSrv.add_event("2021-10-10", "15:00", "descriere 4")
        self.__participationSrv.add_participation(1, 2)
        self.__participationSrv.add_participation(3, 4)

        self.__participationSrv.del_participation(1,2)
        participations = self.__participationSrv.get_all_participations()
        assert(len(participations) == 1)
        assert (participations[0].getPersonID() == 3)
        assert (participations[0].getEventID() == 4)

        self.__participationSrv.del_participation(3,4)
        participations = self.__participationSrv.get_all_participations()
        assert(len(participations) == 0)

        try:
            self.__participationSrv.add_participation(1, 2)
            assert False
        except:
            assert True

if __name__ == '__main__':
    unittest.main()