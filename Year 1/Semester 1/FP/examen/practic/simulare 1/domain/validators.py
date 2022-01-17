from domain.entities import Carte

class ValidatorException(Exception):
    pass

class Validator:
    def __init__(self):
        pass

    def valideazaCarte(self, carte):
        errors = []
        try:
            id = int(carte.getId())
            if id < 0:
                errors.append("id invalid!")
        except ValueError as ve:
                errors.append(str(ve))

        if carte.getAutor() == "":
            errors.append("camp autor gol!")
        if carte.getTitlu() == "":
            errors.append("camp titlu gol!")
        try:
            an = int(carte.getAnAparitie())
            if an > 2022 or an < 0:
                errors.append("an invalid!")
        except ValueError as ve:
                errors.append(str(ve))

        if len(errors) > 0:
            raise ValidatorException(errors)

