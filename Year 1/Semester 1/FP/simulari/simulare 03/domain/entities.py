class Pictura:
    def __init__(self, id, nume, nume_autor, an):
        self.__id = id
        self.__nume = nume
        self.__nume_autor = nume_autor
        self.__an = an

    def getId(self): return self.__id
    def getNume(self): return self.__nume
    def getNumeAutor(self): return self.__nume_autor
    def getAn(self): return self.__an

    def __repr__(self):
        return "ID: " + str(self.__id) + " Nume: " + self.__nume + " Nume Autor: " + self.__nume_autor + " An: " + str(self.__an)

    def __eq__(self, other):
        return self.__id == other.getId()

