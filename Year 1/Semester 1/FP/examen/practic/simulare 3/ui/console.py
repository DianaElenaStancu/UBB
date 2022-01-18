from domain.validator import ValidatorException
from repository.repository import RepositoryException


class Console:
    def __init__(self, service):
        self.__service = service
        self.__cmds = {
            "1": self.__store,
            "2": self.__delete,
            "3": self.__setFiltru,
            "4": self.__undo
        }

    def __printMenu(self):
        print("Comenzi disponibile: ")
        print("0 - exit")
        print("1 - adauga produs")
        print("2 - sterge produs")
        print("3 - seteaza filtru")
        print("4 - undo")


    def run(self):
        exit = False
        while not exit:
            self.__afiseazaFiltrare()
            self.__printMenu()
            cmd = input("Comanda ta este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda invalida")

    def __store(self):
        id = input("Id: ")
        denumire = input("Denumire: ")
        pret = input("Pret: ")
        try:
            produs = self.__service.store(id, denumire, pret)
            print(produs.to_string(), "adaugat cu succes")
        except ValidatorException as ve:
            print(str(ve))
        except RepositoryException as re:
            print(str(re))

    def __delete(self):
        try:
            cifra = int(input("Cifra: "))
        except Exception as e:
            print(str(e))
            return

        nrProduseSterse = self.__service.delete(cifra)
        print("Au fost sterse", nrProduseSterse, "produse")

    def __afiseazaFiltrare(self):
        produse = self.__service.filtrare()
        print("***********")
        for produs in produse:
            print(produs.to_string())
        print("***********")

    def __setFiltru(self):
        try:
            text = input("Text: ")
            pret = int(input("Pret: "))
            self.__service.setFiltru(text, pret)
        except Exception as e:
            print(str(e))

    def __undo(self):
        self.__service.undo()