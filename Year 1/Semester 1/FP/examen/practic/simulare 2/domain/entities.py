from datetime import date, time
class Eveniment:
    def __init__(self, data, ora, descriere):
        """
        initializam un eveniment cu urmatoarele atribute
        :param data: date
        :param ora: time
        :param descriere: str
        """
        self.__data = data
        self.__ora = ora
        self.__descriere = descriere

    #gettere
    def getData(self):
        return self.__data
    def getOra(self):
        return self.__ora
    def getDescriere(self):
        return self.__descriere
    #settere
    def setData(self, value):
        self.__data = value
    def setOra(self, value):
        self.__ora = value
    def setDescriere(self, value):
        self.__descriere = value

    def to_string(self):
        zi = str(self.__data.day)
        if len(zi) == 1:
            zi = "0" + zi
        luna = str(self.__data.month)
        if len(luna) == 1:
            luna = "0" + luna

        dataStr = zi + "." + luna + "." + str(self.__data.year)
        oraStr = str(self.__ora)
        oraStr = oraStr[:-3]
        return dataStr + ";" + oraStr + ';' + self.__descriere


    def __eq__(self, other):
        return self.__data == other.getData() and self.__ora == other.getOra() and self.__descriere == other.getDescriere()
