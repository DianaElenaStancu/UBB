from domain.entities import Eveniment
from utils.conversii import conversieData
from utils.conversii import conversieTimp


class RepositoryException(Exception):
    pass


class Repository():
    def __init__(self, filename):
        self.__filename = filename
        self.__evenimente = []
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            self.__evenimente = []
            for linie in f:
                linie = linie.strip()
                try:
                    attrs = linie.split(";")
                    dataStr = attrs[0]
                    timpStr = attrs[1]
                    descriere = attrs[2]
                    data = conversieData(dataStr)
                    timp = conversieTimp(timpStr)
                    eveniment = Eveniment(data, timp, descriere)
                    self.__evenimente.append(eveniment)
                except:
                    continue

    def __saveToFile(self):
        with open(self.__filename, "w") as f:
            for evenimente in self.__evenimente:
                f.write(evenimente.to_string())
                f.write("\n")

    def store(self, eveniment):
        self.__loadFromFile()
        for e in self.__evenimente:
            if e == eveniment:
                raise RepositoryException("eveniment existent!")
        self.__evenimente.append(eveniment)
        self.__saveToFile()

    def getAll(self):
        self.__loadFromFile()
        return self.__evenimente
