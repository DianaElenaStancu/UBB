"""
produse. se da id, denumire, pret
"""
class Produs:
    def __init__(self, id, denumire, pret):
        self.__id = id
        self.__denumire = denumire
        self.__pret = pret

    def getId(self):
        return self.__id
    def getDenumire(self):
        return self.__denumire
    def getPret(self):
        return self.__pret

    def __eq__(self, other):
        return self.__id == other.getId()

    def to_string(self):
        return str(self.__id) + ";" +  self.__denumire + ";" + str(self.__pret)