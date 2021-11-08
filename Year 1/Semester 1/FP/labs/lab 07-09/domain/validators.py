from domain.entities import Person, Event
from datetime import date, time, datetime

class PersonValidator:

    def validate_name(self, name):
        if name == '':
            raise ValueError("Trebuie sa introduceti numele persoanei")

    def validate_address(self, address):
        if address == '':
            raise ValueError("Trebuie sa introduceti adresa persoanei")

    def validate(self, person):
        errors = []
        if person.getName() == '':
            errors.append("Trebuie sa introduceti numele persoanei")
        if person.getAddress() == '':
            errors.append("Trebuie sa introduceti adresa persoanei")

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValueError(error_string)



def test_validate_person():
    validator = PersonValidator()
    p = Person('John', 'Str Zorilor Nr 12')
    validator.validate(p)

    p1 = Person('', 'Str Zorilor Nr 12')
    try:
        validator.validate(p1)
        assert False
    except ValueError:
        assert True

    p2 = Person('Tom', '')
    try:
        validator.validate(p2)
        assert False
    except ValueError:
        assert True

    p3 = Person('', '')
    try:
        validator.validate(p3)
        assert False
    except ValueError:
        assert True

def test_validate_person_name():
    validator = PersonValidator()
    name = ""
    try:
        validator.validate_name(name)
        assert False
    except ValueError:
        assert True

    name = "ana"
    try:
        validator.validate_name(name)
        assert True
    except ValueError:
        assert False

def test_validate_person_address():
    validator = PersonValidator()
    address = ""
    try:
        validator.validate_address(address)
        assert False
    except ValueError:
        assert True

    address = "Str zorilor"
    try:
        validator.validate_address(address)
        assert True
    except ValueError:
        assert False


class EventValidator:

    def validate_date(self, value):
        try:
            date.fromisoformat(value)
        except ValueError as ve:
            raise ValueError(str(ve))

    def validate_time(self, time):
        try:
            datetime.strptime(time, "%H:%M")
        except ValueError as ve:
            raise ValueError(str(ve))

    def validate_description(self, value):
        if value == '':
            raise ValueError("Trebuie sa introduceti descrierea evenimentului")

    def validate(self, event):
        errors = []
        try:
            date.fromisoformat(event.getDate())
        except ValueError as ve:
            errors.append(str(ve))

        try:
            datetime.strptime(event.getTime(), "%H:%M")
        except ValueError as ve:
            errors.append(str(ve))

        if event.getDescription() == '':
            errors.append("Trebuie sa introduceti descrierea evenimentului")

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValueError(error_string)


def test_validate_event():
    validator = EventValidator()
    e = Event(1, date(2020, 11, 30), time(16, 0, 0, 0), "botezul Anei")
    validator.validate(e)

    e1 = Event(1, date(2020, 11, 30), time(16, 0, 0, 0), "")
    try:
        validator.validate(e1)
        assert False
    except ValueError:
        assert True

def test_validate_event_date():
    validator = EventValidator()
    date = "210jsa-dhsa"
    try:
        validator.validate_date(date)
        assert False
    except ValueError:
        assert True

    date = "2020-10-10"
    try:
        validator.validate_date(date)
        assert True
    except ValueError:
        assert False

def test_validate_event_time():
    validator = EventValidator()
    time = "16.00"
    try:
        validator.validate_time(time)
        assert False
    except ValueError:
        assert True

    time = "16:00"
    try:
        validator.validate_time(time)
        assert True
    except ValueError:
        assert False

def test_validate_event_description():
    validator = EventValidator()
    description = ""
    try:
        validator.validate_description(description)
        assert False
    except ValueError:
        assert True

    description = "bla bla bla"
    try:
        validator.validate_description(description)
        assert True
    except ValueError:
        assert False