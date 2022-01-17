class Bug:
    def __init__(self, id, componenta_afectata, descriere, prioritate):
        """
        creez o noua instanta de tip Bug care urmatoarele atribute
        :param id: id-ul bugului
        :type id: int
        :param componenta_afectata: numele componentei afectate de bug
        :type componenta_afectata: str
        :param descriere: descriere a bugului
        :type descriere: str
        :param prioritate: prioritatea pe care o are bugul
        :type prioritate: int
        """
        self.__id = id
        self.__componenta_afectata = componenta_afectata
        self.__descriere = descriere
        self.__prioritate = prioritate

    #getter methods
    def getId(self):
        return self.__id

    def getComponentaAfectata(self):
        return self.__componenta_afectata

    def getDescriere(self):
        return self.__descriere

    def getPrioritate(self):
        return self.__prioritate

    #supraincarcare de operatori
    #definim ce inseamna ca doua instante de tipul Bug sa fie egale
    def __eq__(self, other):
        """doua instante de tipul Bug sunt egale daca si numai daca au acelasi id"""
        return self.__id == other.getId()

    #definim modul de reprezentare a unei instante de tip bug
    def __repr__(self):
        """"""
        return "- Id: " + str(self.__id) + "; - Numele componentei afectate: " + self.__componenta_afectata + "; - Descriere: " + self.__descriere + "; - Prioritate: " + str(self.__prioritate)
