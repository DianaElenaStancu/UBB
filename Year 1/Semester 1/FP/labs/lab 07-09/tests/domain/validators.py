from datetime import date, time
from app.domain.entities import Person, Event
from app.domain.validators import PersonValidator, EventValidator
from app.exceptions.exceptions import ValidatorException

def test_validate_person():
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

def test_validate_person_name():
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

def test_validate_person_address():
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


def test_validate_event():
    validator = EventValidator()
    e = Event(1, "2020-11-30", "16:00", "botezul Anei")
    validator.validate(e)

    e1 = Event(2, "2020-11-30", "16:00", "")
    try:
        validator.validate(e1)
        assert False
    except ValidatorException:
        assert True

def test_validate_event_date():
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

def test_validate_event_time():
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

def test_validate_event_description():
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

