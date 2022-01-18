from domain.entities import Produs


class ValidatorException(Exception):
    pass

class Validator:
    def valideazaProdus(self, produs):
        errors = []
        try:
            id = int(produs.getId())
        except Exception as e:
            raise ValidatorException(str(e))
        try:
            pret = int(produs.getPret())
        except Exception as e:
            raise ValidatorException(str(e))
        if id < 0:
            errors.append("id invalid;")
        if produs.getDenumire() == "":
            errors.append("denumire invalida;")
        if pret < 0:
            errors.append("pret invalid;")

        if len(errors) > 0:
            raise ValidatorException(errors)


