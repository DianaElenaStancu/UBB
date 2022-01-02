from datetime import date, time
from app.domain.entities import Person, Event
from app.domain.validators import PersonValidator, EventValidator
from app.exceptions.exceptions import ValidatorException
import unittest

class TestValidator(unittest.TestCase):
    def setUp(self) -> None:
        self.__pValidator = PersonValidator()
        self.__eValidator = EventValidator()

    def test_validate_person(self):
        p = Person(1, 'John', 'Str Zorilor Nr 12')
        self.__pValidator.validate(p)

        p1 = Person(2, '', 'Str Zorilor Nr 12')
        try:
            self.__pValidator.validate(p1)
            assert False
        except ValidatorException:
            assert True

        p2 = Person(3, 'Tom', '')
        try:
            self.__pValidator.validate(p2)
            assert False
        except ValidatorException:
            assert True

        p3 = Person(4, '', '')
        try:
            self.__pValidator.validate(p3)
            assert False
        except ValidatorException:
            assert True

    def test_validate_person_name(self):
        name = ""
        try:
            self.__pValidator.validate_name(name)
            assert False
        except ValidatorException:
            assert True

        name = "ana"
        try:
            self.__pValidator.validate_name(name)
            assert True
        except ValidatorException:
            assert False

    def test_validate_person_address(self):
        address = ""
        try:
            self.__pValidator.validate_address(address)
            assert False
        except ValidatorException:
            assert True

        address = "Str zorilor"
        try:
            self.__pValidator.validate_address(address)
            assert True
        except ValidatorException:
            assert False


    from app.exceptions.exceptions import ValidatorException


    def test_validate_event(self):
        e = Event(1, "2020-11-30", "16:00", "botezul Anei")
        self.__eValidator.validate(e)

        e1 = Event(2, "2020-11-30", "16:00", "")
        try:
            self.__eValidator.validate(e1)
            assert False
        except ValidatorException:
            assert True

    def test_validate_event_date(self):
        date = "210jsa-dhsa"
        try:
            self.__eValidator.validate_date(date)
            assert False
        except ValidatorException:
            assert True

        date = "2020-10-10"
        try:
            self.__eValidator.validate_date(date)
            assert True
        except ValidatorException:
            assert False

    def test_validate_event_time(self):
        time = "16.00"
        try:
            self.__eValidator.validate_time(time)
            assert False
        except ValidatorException:
            assert True

        time = "16:00"
        try:
            self.__eValidator.validate_time(time)
            assert True
        except ValidatorException:
            assert False

    def test_validate_event_description(self):
        description = ""
        try:
            self.__eValidator.validate_description(description)
            assert False
        except ValidatorException:
            assert True

        description = "bla bla bla"
        try:
            self.__eValidator.validate_description(description)
            assert True
        except ValidatorException:
            assert False

if __name__ == '__main__':
    unittest.main()
