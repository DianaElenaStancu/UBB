class TvShow:
    def __init__(self, id, titlu, gen, numar_total_eps):
        """
        Creeaza o noua instanta TvShow cu urmatoarele atribute
        :param id: id-ul TvShow-ului
        :type id: str
        :param titlu: titlul TvShow-ului
        :type titlu: str
        :param gen: genul TvShow-ului
        :type gen: str
        :param numar_total_eps: numarul de episoade a TvShow-ului
        :type numar_total_eps: int
        """
        self.__id = id
        self.__titlu = titlu
        self.__gen = gen
        self.__numar_total_eps = numar_total_eps

    #gettere

    def getId(self):
        return self.__id

    def getTitlu(self):
        return self.__titlu

    def getGen(self):
        return self.__gen

    def getNumarEps(self):
        return self.__numar_total_eps

    def __eq__(self, other):
        return self.__id == other.getId()

    def __repr__(self):
        return "Show ID: " + self.__id + " Titlu: " + self.__titlu + " Gen: " + self.__gen + "Numar total de episoade: " + str(self.__numar_total_eps)

class ShowEvaluation:
    def __init__(self, tv_show, numar_ore):
        self.__tv_show = tv_show
        self.__numar_ore = numar_ore


    def get_preference(self):
        if (2*self.__tv_show.getNumarEps())//3 < self.__numar_ore:
            return "favorite"
        elif (self.__tv_show.getNumarEps())//3 < (self.__numar_ore):
            return "if_bored"
        else:
            return "disliked"
