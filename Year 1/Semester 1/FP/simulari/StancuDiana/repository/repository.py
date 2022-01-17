from domain.entities import Bug

class RepoException(Exception):
    pass

class Repository:
    def __init__(self, filename):
        """
        :param filename: pathul fisierului din care trebuie incarcate datele
        :type filename: str
        post: bug-urile sunt incarcate din fisier
        """
        self.__filename = filename
        self.__bugs = []
        self.__loadFromFile()

    def __loadFromFile(self):
        """incarc in memorie toate datele din fisierul cu pathul self.__filename"""
        with open(self.__filename, "r") as f:
            self.__bugs = []
            for linie in f:
                linie = linie.strip()
                try:
                    attrs = linie.split(",")
                    id = int(attrs[0])
                    componenta_afectata = attrs[1]
                    descriere = attrs[2]
                    prioritate = int(attrs[3])
                    bug = Bug(id, componenta_afectata, descriere, prioritate)
                    self.__bugs.append(bug)
                except:
                    continue

    def getAll(self):
        return self.__bugs