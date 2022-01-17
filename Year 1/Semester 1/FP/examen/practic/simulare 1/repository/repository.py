from domain.entities import Carte

class RepositoryException(Exception):
    pass

class Repository:
    def __init__(self, filename):
        """
        :param filename: path-ul fisierului din care trebuie incarcate datele
        :type filename: str
        post: cartile sunt incarcate in fisier
        """
        self.__filename = filename
        self.__carti = []
        self.__history = []
        self.__loadFromFile()
        self.__initHistory()

    def __loadFromFile(self):
        """incarc in memorie toate datele din fisierul cu pathul self.__filename """
        with open(self.__filename, "r") as f:
            self.__carti = []
            for linie in f:
                linie  = linie.strip()
                try:
                    attrs = linie.split(";")
                    id = int(attrs[0])
                    titlu = attrs[1]
                    autor = attrs[2]
                    anAparitie = int(attrs[3])
                    carte = Carte(id, titlu, autor, anAparitie)
                    self.__carti.append(carte)
                except:
                    continue

    def __initHistory(self):
        self.__history.append(self.__carti)

    def __saveToFile(self):
        with open(self.__filename, "w") as f:
            for carte in self.__carti:
                f.write(carte.to_string())

    def modificaAutorCarte(self, carte, autor):
        self.__loadFromFile()
        indexCarteCautata = self.__carti.index(carte)
        carteCautata = self.__carti[indexCarteCautata]
        carteCautata.setAutor(autor)
        self.__saveToFile()
        self.__history.append(self.__carti)

    def store(self, carte):
        self.__loadFromFile()
        self.__carti.append(carte)
        self.__saveToFile()
        self.__history.append(self.__carti)

    def existaCarte(self, carteCautata):
        for carte in self.__carti:
            print(carte.to_string(), carteCautata.to_string(), carte == carteCautata)
            if carte == carteCautata:
                raise RepositoryException("carte existenta!")

    def undo(self):
        if len(self.__history) > 1:
            self.__history.pop()
            self.__carti = self.__history[-1]
            self.__saveToFile()

    def getAll(self):
        self.__loadFromFile()
        return self.__carti
