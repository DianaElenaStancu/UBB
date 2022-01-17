from domain.validators import ValidatorException
from repository.repository import RepositoryException


class Console:
    def __init__(self, service):
        self.__service = service
        self.__cmds = {
            "1": self.__adaugaCarte,
            "2": self.__modificaCarte,
            "3": self.__afiseazaCarti,
            "4": self.__undo,
            "5": self.__filtru
        }

    def __printMenu(self):
        print("Comenzi:")
        print("0 - exit")
        print("1 - adauga carte noua")
        print("2 - modifica carte")
        print("3 - afiseaza carti")
        print("4 - undo")
        print("5 - modifica filtru")

    def run(self):
        exit = False
        carti = self.__service.filtreazaCarti()
        self.__afiseazaCarti1(carti)
        while not exit:
            self.__printMenu()
            cmd = input("Comanda este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda invalida")

    def __filtru(self):
        try:
            text = input("text: ")
            an = int(input("an: "))
            self.__service.modificaFiltru(text, an)
            carti = self.__service.filtreazaCarti()
            self.__afiseazaCarti1(carti)
        except ValueError as ve:
            print(str(ve))

    def __afiseazaCarti1(self, carti):
        for carte in carti:
            print(carte.to_string())

    def __adaugaCarte(self):
        try:
            id = int(input("Id-ul cartii: "))
            titlu = input("Titlul cartii: ")
            autor = input("Autorul cartii: ")
            anAparitie = int(input("Anul in care a aparut cartea: "))
        except ValueError as ve:
            print(str(ve))
            return
        try:
            carte = self.__service.adaugaCarte(id, titlu, autor, anAparitie)
            print(carte.to_string() + " adaugata cu succes")
        except ValidatorException as ve:
            print(str(ve))
        except RepositoryException as re:
            print(str(re))

    def __modificaCarte(self):
        try:
            cifra = int(input("Cifra care trebuie sa fie in id: "))
            autor = input("Numele autorului: ")
            if autor == "":
                print("campul cu numele e gol!")
                return
            self.__service.modificaAutor(cifra, autor)
        except ValueError as ve:
            print(str(ve))

    def __afiseazaCarti(self):
        carti = self.__service.getAll()
        for carte in carti:
            print(carte.to_string())

    def __undo(self):
        self.__service.undo()
