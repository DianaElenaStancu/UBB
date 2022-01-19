class ValidatorException(Exception):
    pass

class Validator:
    def valideaza_piesa(self, piesa):
        errors = []
        if piesa.get_gen() not in ["comedie", "drama", "satira", "altele"]:
            errors.append("gen invalid")
        if piesa.get_titlu() == "":
            errors.append("titlu gol")
        if piesa.get_regizor() == "":
            errors.append("piesa gol")
        if piesa.get_durata() < 0:
            errors.append("durata invalida")

        if len(errors) > 0:
            raise ValidatorException(errors)