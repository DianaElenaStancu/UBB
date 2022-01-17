#5:23
class Carte():
    def __init__(self, id, titlu, autor, anAparitie):
        """
        initializeaza un obiect de tip carte cu valorile date
        :param id: id-ul cartii;int
        :param titlu: titlul cartii;str
        :param autor: autorul cartii;str
        :param anAparitie: anul in care a aparut cartea;date
        """
        self.__id = id
        self.__titlu = titlu
        self.__autor = autor
        self.__anAparitie = anAparitie

    #definim gettere si settere
    def getId(self):
        return self.__id
    def getTitlu(self):
        return self.__titlu
    def getAutor(self):
        return self.__autor
    def getAnAparitie(self):
        return self.__anAparitie
    def setTitlu(self, value):
        self.__titlu = value
    def setAutor(self, value):
        self.__autor = value
    def setAnAparitie(self, value):
        self.__anAparitie = value

    def to_string(self):
        return str(self.__id) + ";" + self.__titlu + ";" + self.__autor + ";" + str(self.__anAparitie) + "\n"

    def __eq__(self, other):
        return self.getId() == other.getId()

