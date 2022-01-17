from domain.entities import Carte
from domain.validators import Validator, ValidatorException
from repository.repository import Repository, RepositoryException
from service.service import Service
from utils.utils import existaCifra


class Test:
    def runAll(self):
        self.__testEntities()
        self.__testValidator()
        self.__testRepository()
        self.__testService()
        self.__testUtils()

    def __testEntities(self):
        carte1 = Carte(1, "ana", "are", 1989)
        carte2 = Carte(2, "aba", "djsaods", 1976)
        assert carte1.getId() == 1
        assert carte1.getTitlu() == "ana"
        assert carte1.getAutor() == "are"
        assert carte1.getAnAparitie() == 1989
        assert carte1 != carte2
        assert carte1 == carte1

        carte1.setAutor("cristi")
        assert carte1.getAutor() == "cristi"

    def __testValidator(self):
        val = Validator()
        carte1 = Carte(1, "ana", "are", 1989)
        carte2 = Carte(2, "aba", "", 1976)
        carte3 = Carte(-1, "aba", "", "hdaihfd")
        val.valideazaCarte(carte1)

        try:
            val.valideazaCarte(carte2)
            assert False
        except ValidatorException:
            assert True

        try:
            val.valideazaCarte(carte3)
            assert False
        except ValidatorException:
            assert True



    def __testRepository(self):
        with open("testing/cartiTest.txt", "w") as f:
            f.write("1;ana;are;1987")
            f.write("\n")
            f.write("2;dsa;ss;")
            f.write("\n")
            f.write("2;aba;djsaods;1976")
        repo = Repository("testing/cartiTest.txt")
        carte1 = Carte(1, "ana", "are", 1989)
        carte2 = Carte(2, "aba", "djsaods", 1976)
        carti = repo.getAll()
        assert len(carti) == 2
        assert carti[0] == carte1
        assert carti[1] == carte2
        repo.modificaAutorCarte(carte1, "mirabela")
        carti = repo.getAll()
        assert len(carti) == 2
        assert carti[0] == carte1
        assert carti[1] == carte2
        assert carti[0].getAutor() == "mirabela"

        carte3 = Carte(4, "aba", "djsaods", 1976)
        repo.store(carte3)
        carti = repo.getAll()
        assert len(carti) == 3
        assert carti[0] == carte1
        assert carti[1] == carte2
        assert carti[2] == carte3

        carte4 = Carte(9, "aba", "djsaods", 1976)
        repo.existaCarte(carte4)

        try:
            repo.existaCarte(carte3)
            assert False
        except RepositoryException:
            assert True


    def __testService(self):
        with open("testing/cartiTest.txt", "w") as f:
            f.write("1;ana;are;1987")
            f.write("\n")
            f.write("2;dsa;ss;")
            f.write("\n")
            f.write("2;aba;djsaods;1976")
        repo = Repository("testing/cartiTest.txt")
        validator = Validator()
        service = Service(repo, validator)
        carte1 = Carte(1, "ana", "are", 1989)
        carte2 = Carte(2, "aba", "djsaods", 1976)
        carte3 = Carte(7, "aba", "djsaods", 1976)
        carte4 = Carte(10, "ana", "are", 1989)

        service.adaugaCarte(7, "aba", "djsaods", 1976)

        try:
            service.adaugaCarte(-9, "", "", 98)
            assert False
        except ValidatorException:
            assert True

        try:
            service.adaugaCarte(1, "ana", "are", 1989)
            assert False
        except RepositoryException:
            assert True

        carti = service.getAll()
        assert len(carti) == 3
        assert carti[0] == carte1
        assert carti[1] == carte2
        assert carti[2] == carte3


        service.adaugaCarte(10, "aba", "djsaods", 1976)
        service.modificaAutor(1, "carina")
        carti = service.getAll()
        carte1 = Carte(1, "ana", "carina", 1989)
        carte4 = Carte(10, "ana", "carina", 1989)

        assert len(carti) == 4
        assert carti[0] == carte1
        assert carti[1] == carte2
        assert carti[2] == carte3
        assert carti[3] == carte4


    def __testUtils(self):
        assert existaCifra(100, 0) == True
        assert existaCifra(1, 0) == False
        assert existaCifra(123456789, 0) == False
        assert existaCifra(0,0) == True
        assert existaCifra(1, 1) == True

