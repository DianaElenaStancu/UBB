from domain.entities import Pictura


class Repo():
    def __init__(self, filename):
        self.__filename = filename
        self.__picturi = []
        self.__loadFromFile()

    def __loadFromFile(self):
        with open(self.__filename, "r") as f:
            self.__picturi = []
            for linie in f:
                linie = linie.strip()
                if linie == "":
                    continue
                attrs = linie.split(",")
                id = int(attrs[0])
                nume = attrs[1]
                nume_autor = attrs[2]
                an = int(attrs[3])
                pictura = Pictura(id, nume, nume_autor, an)
                self.__picturi.append(pictura)

    def getAll(self):
        return self.__picturi
