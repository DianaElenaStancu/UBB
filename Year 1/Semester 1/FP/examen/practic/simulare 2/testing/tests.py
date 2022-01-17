from domain.entities import Eveniment
from datetime import date, time

from domain.validator import Validator, ValidatorException
from repository.repository import Repository


class Test:
    def __init__(self):
        pass


    def runAll(self):
        self.__testEntities()
        self.__testValidator()
        self.__testRepository()

    def __testEntities(self):
        e1 = Eveniment(date(2021, 2, 20), time(8, 0), "Exam FP")
        e2 = Eveniment(date(2021, 1, 20), time(10, 0), "Exam LC")
        assert e1.getData() == date(2021, 2, 20)
        assert e1.getOra() == time(8, 0)
        assert e1.getDescriere() == "Exam FP"
        assert e1 == e1
        assert e1 != e2
        assert e1.to_string() == "20.02.2021;08:00;Exam FP"

    def __testValidator(self):
        e1 = Eveniment("20.02.2021", "08:00", "dhsaodhsa")
        e2 = Eveniment("20.02.2021", "8:00", "dhsaodhsa")
        e3 = Eveniment("20.02.2021", "8:00", "")
        e4 = Eveniment("2002.2021", "08:00", "dsa")
        validator = Validator()
        validator.valideazaEveniment(e1)
        try:
            validator.valideazaEveniment(e2)
            assert False
        except ValidatorException as ve:
            assert True
        try:
            validator.valideazaEveniment(e3)
            assert False
        except ValidatorException:
            assert True
        try:
            validator.valideazaEveniment(e4)
            assert False
        except ValidatorException:
            assert True

    def __testRepository(self):
        with open("testing/test.txt", "w") as f:
            f.write("20.02.2021;08:00;Exam FP")
            f.write("\n")
            f.write("202.2021;dss08:00;dhsadhsa")
            f.write("\n")
            f.write("20.01.2021;08:00;mna")
        repo = Repository("testing/test.txt")
        e1 = Eveniment(date(2021, 2, 20), time(8, 0), "Exam FP")
        e2 = Eveniment(date(2021, 1, 20), time(8, 0), "mna")
        evenimente = repo.getAll()
        assert len(evenimente) == 2
        assert evenimente[0] == e1
        assert evenimente[1] == e2


