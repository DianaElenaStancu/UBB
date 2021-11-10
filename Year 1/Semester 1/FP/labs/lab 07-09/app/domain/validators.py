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
        try:
            self.validate_name(person.getName())
        except ValueError as ve:
            errors.append(str(ve))

        try:
            self.validate_address(person.getAddress())
        except ValueError as ve:
            errors.append(str(ve))

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValueError(error_string)


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
            self.validate_date(event.getDate())
        except ValueError as ve:
            errors.append(str(ve))

        try:
            self.validate_time(event.getTime())
        except ValueError as ve:
            errors.append(str(ve))

        try:
            self.validate_description(event.getDescription())
        except ValueError as ve:
            errors.append(str(ve))

        if len(errors) > 0:
            error_string = '\n'.join(errors)
            raise ValueError(error_string)