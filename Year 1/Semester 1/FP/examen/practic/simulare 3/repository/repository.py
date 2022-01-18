from domain.entities import Produs
from utils.utils import cifraInNumar


class RepositoryException(Exception):
    pass

class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__produse = []
        self.__loadFromFile()
        self.__historyDelete = []

    def __loadFromFile(self):
        with open(self.__filename, 'r') as f:
            self.__produse = []
            for linie in f:
                linie = linie.strip()
                try:
                    attrs = linie.split(";")
                    id = int(attrs[0])
                    denumire = attrs[1]
                    pret = int(attrs[2])
                    produs = Produs(id, denumire, pret)
                    self.__produse.append(produs)
                except:
                    continue

    def __saveToFile(self):
        with open(self.__filename, 'w') as f:
            for produs in self.__produse:
                f.write(produs.to_string())
                f.write("\n")

    def store(self, produs):
        if produs in self.__produse:
            raise RepositoryException("produs cu id deja existent!")
        self.__produse.append(produs)
        self.__saveToFile()

    def delete(self, produse):
        if len(produse) > 0:
            copy = self.__produse[:]
            self.__historyDelete.append(copy)
            for produs in produse:
                self.__produse.remove(produs)
            self.__saveToFile()

    def undo(self):
        if len(self.__historyDelete) > 0:
            self.__produse = self.__historyDelete[-1]
            self.__historyDelete.pop()
            self.__saveToFile()


    def cautaDupaPret(self, cifra):
        produseCautate = []
        for produs in self.__produse:
            if cifraInNumar(produs.getPret(), cifra):
                produseCautate.append(produs)
        return produseCautate

    def getAll(self):
        self.__loadFromFile()
        return self.__produse