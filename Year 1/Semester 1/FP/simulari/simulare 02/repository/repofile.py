from domain.entities import TvShow

class RepoException(Exception):
    pass

class Repo():
    def __init__(self, filename):
        self.__filename = filename
        self.__TvShows = []
        self.__loadFromFile()

    def __loadFromFile(self):
        """incarc in memorie toate datele din fisierului cu pathul dat"""
        with open(self.__filename, "r") as f:
            self.__TvShows = []
            for linie in f:
                linie = linie.strip()
                if linie == "":
                    continue
                attrs = linie.split(",")
                #<id_show>, <titlu>, <gen>, <număr_total_eps>
                id = attrs[0]
                titlu = attrs[1]
                gen = attrs[2]
                numar_total_eps = int(attrs[3])
                tv_show = TvShow(id, titlu, gen, numar_total_eps)
                self.__TvShows.append(tv_show)

    def cauta_dupa_ID(self, id):
        tv_shows = self.getAll()
        for show in tv_shows:
            if id == show.getId():
                return show
        raise RepoException("Nu exista show cu id-ul dat")

    def getAll(self):
        return self.__TvShows