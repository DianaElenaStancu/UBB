from domain.entities import Elicopter


class RepoFile():
    def __init__(self, filename):
        """
        :param filename: pathul fisierului unde sunt stocate elicopterele
        :type filename: str
        post: elicopterele sunt incarcate din fisier in memorie
        """
        self.__filename = filename
        self.__elicoptere = []
        #incarcam elicopterele din fisier
        self.__loadFromFile()

    def __loadFromFile(self):
        """incarc in memorie toate datele din fisierul cu numele filename"""
        with open(self.__filename, "r") as f:
            self.__elicoptere = []
            for linie in f:
                linie = linie.strip()
                if linie == "":
                    continue
                attrs = linie.split(",")
                id = int(attrs[0])
                nume = attrs[1]
                scopuri = attrs[2]
                anFabricatie = int(attrs[3])
                elicopter = Elicopter(id, nume, scopuri, anFabricatie)
                #incarcam in memorie
                self.__elicoptere.append(elicopter)

    def getAll(self):
        return self.__elicoptere






