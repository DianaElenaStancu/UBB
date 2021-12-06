from datetime import date, time, datetime

from app.exceptions.exceptions import ValidatorException


class PersonValidator:

    def validate_id(self, id):
        if id < 0:
            raise ValidatorException("Id invalid")

    def validate_name(self, name):
        if name == '':
            raise ValidatorException("Trebuie sa introduceti numele persoanei")

    def validate_address(self, address):
        if address == '':
            raise ValidatorException("Trebuie sa introduceti adresa persoanei")

    def validate(self, person):
        errors = []

        try:
            self.validate_id(person.getID())
        except ValidatorException as ve:
            errors.append(str(ve))

        try:
            self.validate_name(person.getName())
        except ValidatorException as ve:
            errors.append(str(ve))

        try:
            self.validate_address(person.getAddress())
        except ValidatorException as ve:
            errors.append(str(ve))

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValidatorException(error_string)


class EventValidator:

    def validate_date(self, value):
        try:
            date.fromisoformat(value)
        except ValidatorException as ve:
            raise ValidatorException(str(ve))

    def validate_time(self, time):
        try:
            datetime.strptime(time, "%H:%M")
        except ValidatorException as ve:
            raise ValidatorException(str(ve))

    def validate_description(self, value):
        if value == '':
            raise ValidatorException("Trebuie sa introduceti descrierea evenimentului")

    def validate(self, event):
        errors = []

        try:
            self.validate_date(event.getDate())
        except ValidatorException as ve:
            errors.append(str(ve))

        try:
            self.validate_time(event.getTime())
        except ValidatorException as ve:
            errors.append(str(ve))

        try:
            self.validate_description(event.getDescription())
        except ValidatorException as ve:
            errors.append(str(ve))

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValidatorException(error_string)

class ParticipationValidator:
    pass