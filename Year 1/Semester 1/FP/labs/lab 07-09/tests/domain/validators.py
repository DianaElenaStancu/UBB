from datetime import date, time
from app.domain.entities import Person, Event
from app.domain.validators import PersonValidator, EventValidator
from app.exceptions.exceptions import ValidatorException


class validator_TEST():
    def run(self):
        self.__test_validate_person()
        self.__test_validate_event()
        self.__test_validate_event_time()
        self.__test_validate_event_date()
        self.__test_validate_person_address()
        self.__test_validate_event_description()
        self.__test_validate_person_name()

    def __test_validate_person(self):
        validator = PersonValidator()
        p = Person(1, 'John', 'Str Zorilor Nr 12')
        validator.validate(p)

        p1 = Person(2, '', 'Str Zorilor Nr 12')
        try:
            validator.validate(p1)
            assert False
        except ValidatorException:
            assert True

        p2 = Person(3, 'Tom', '')
        try:
            validator.validate(p2)
            assert False
        except ValidatorException:
            assert True

        p3 = Person(4, '', '')
        try:
            validator.validate(p3)
            assert False
        except ValidatorException:
            assert True

    def __test_validate_person_name(self):
        validator = PersonValidator()
        name = ""
        try:
            validator.validate_name(name)
            assert False
        except ValidatorException:
            assert True

        name = "ana"
        try:
            validator.validate_name(name)
            assert True
        except ValidatorException:
            assert False

    def __test_validate_person_address(self):
        validator = PersonValidator()
        address = ""
        try:
            validator.validate_address(address)
            assert False
        except ValidatorException:
            assert True

        address = "Str zorilor"
        try:
            validator.validate_address(address)
            assert True
        except ValidatorException:
            assert False


    from app.exceptions.exceptions import ValidatorException


    def __test_validate_event(self):
        validator = EventValidator()
        e = Event(1, "2020-11-30", "16:00", "botezul Anei")
        validator.validate(e)

        e1 = Event(2, "2020-11-30", "16:00", "")
        try:
            validator.validate(e1)
            assert False
        except ValidatorException:
            assert True

    def __test_validate_event_date(self):
        validator = EventValidator()
        date = "210jsa-dhsa"
        try:
            validator.validate_date(date)
            assert False
        except ValidatorException:
            assert True

        date = "2020-10-10"
        try:
            validator.validate_date(date)
            assert True
        except ValidatorException:
            assert False

    def __test_validate_event_time(self):
        validator = EventValidator()
        time = "16.00"
        try:
            validator.validate_time(time)
            assert False
        except ValidatorException:
            assert True

        time = "16:00"
        try:
            validator.validate_time(time)
            assert True
        except ValidatorException:
            assert False

    def __test_validate_event_description(self):
        validator = EventValidator()
        description = ""
        try:
            validator.validate_description(description)
            assert False
        except ValidatorException:
            assert True

        description = "bla bla bla"
        try:
            validator.validate_description(description)
            assert True
        except ValidatorException:
            assert False

