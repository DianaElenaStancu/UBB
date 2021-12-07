class Elicopter:
    def __init__(self, id, nume, scopuri, anFabricatie):
        """
        Creaza o noua instanta Elicopter cu urmatoarele atribute:
        :param id: id-ul elicopterului
        :type id: int
        :param nume: numele elicopterului
        :type nume: str
        :param scopuri: sir de scopuri ale elicopterului
        :type scopuri: str
        :param anFabricatie: anul in care a fost fabricat elicopterul
        """
        self.__id = id
        self.__nume = nume
        self.__scopuri = scopuri
        self.__anFabricatie = anFabricatie

    #getter methods

    def getId(self):
        return self.__id

    def getNume(self):
        return self.__nume

    def getScopuri(self):
        return self.__scopuri

    def getAnFabricatie(self):
        return self.__anFabricatie

    def __eq__(self, other):
        return self.__id == other.getId()

    def __repr__(self):
        return "Elicopter: ID - " + str(self.__id) + " NUME - " + str(self.__nume) + " SCOPURI - " + str(self.__scopuri) + " AN FABRICATIE - " + str(self.__anFabricatie)


