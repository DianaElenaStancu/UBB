from domain.entities import Produs
from domain.validator import Validator
from repository.repository import Repository
from utils.utils import cifraInNumar


class Testing:
    def run(self):
        self.__testEntities()
        self.__testValidator()
        self.__testRepository()
        self.__testUtils()

    def __testEntities(self):
        p1 = Produs(1, 'ciocolata', 5)
        p2 = Produs(2, 'bezele', 6)
        assert p1.getId() == 1
        assert p1.getPret() == 5
        assert p1.getDenumire() == 'ciocolata'
        assert p1 == p1
        assert p1 != p2
        assert p1.to_string() == "1;ciocolata;5"

    def __testValidator(self):
        p1 = Produs(1, 'ciocolata', 5)
        p2 = Produs(2, '', 6)
        p3 = Produs(-2, '', 6)
        p4 = Produs(-2, '', 'asd')
        validator = Validator()
        validator.valideazaProdus(p1)
        try:
            validator.valideazaProdus(p2)
            assert False
        except:
            assert True
        try:
            validator.valideazaProdus(p3)
            assert False
        except:
            assert True
        try:
            validator.valideazaProdus(p4)
            assert False
        except:
            assert True


    def __testRepository(self):
        with open("testing/productTest.txt", 'w') as f:
            f.write("1;ciocolata;5")
            f.write("\n")
            f.write("\n")
            f.write("1s;ciocolata;5")
            f.write("\n")
            f.write("2;bezele;6")
        repo = Repository("testing/productTest.txt")
        p1 = Produs(1, 'ciocolata', 5)
        p2 = Produs(2, 'bezele', 6)
        produse = repo.getAll()
        assert len(produse) == 2
        assert produse[0] == p1
        assert produse[1] == p2

        produse = [p1]
        repo.delete(produse)
        produse = repo.getAll()
        assert len(produse) == 1
        assert produse[0] == p2

        repo.store(p1)
        produse = repo.getAll()
        assert len(produse) == 2
        assert produse[1] == p1
        assert produse[0] == p2

    def __testUtils(self):
        assert cifraInNumar(35, 5) == True
        assert cifraInNumar(35, 6) == False