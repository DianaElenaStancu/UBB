from datetime import date, time

from utils.conversii import conversieData, conversieTimp


class ValidatorException(Exception):
    pass

class Validator:
    def __init__(self):
        pass
    def valideazaEveniment(self, eveniment):
        errors = []
        try:
            conversieData(eveniment.getData())
        except Exception as ve:
            errors.append(str(ve))
        try:
            conversieTimp(eveniment.getOra())
        except Exception as ve:
            errors.append(str(ve))

        if(eveniment.getDescriere() == ""):
            errors.append("camp descriere gol!")

        if len(errors) > 0:
            raise ValidatorException(str(errors))