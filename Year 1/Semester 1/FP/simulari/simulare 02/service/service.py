from domain.entities import ShowEvaluation


class Service:
    def __init__(self, repo):
        self.__repo = repo


    #1Căutarea de show-uri pe baza genului show-ului. Utilizatorul introduce un string, aplicația tipărește
    #toate show-urile disponibile pentru care genul conține stringul dat de utilizator.
    def cauta_dupa_gen(self, gen):
        tv_shows = self.__repo.getAll()
        tv_shows_cautate = []
        for show in tv_shows:
            if gen in show.getGen():
                tv_shows_cautate.append(show)
        return tv_shows_cautate

    #Returnare informații privind preferințele utilizatorului. Utilizatorul introduce id-ul show-ului tv
    #și numărul de episoade pe care le-a văzut din acest serial.Aplicația tipărește titlul serialului, genul
    #din care face parte, și preferința utilizatorului
    def preferinte_utilizator(self, id, nr_eps_vizionate):
        """
        functi returneaza tv_show-ul cu id-ul dat cat si preferinta utilizatorului dupa cum urmeaza:
                Dacă utilizatorul a vizionat mai mult de 2/3 din numărul total de episoade: favorit
                Dacă utilizatorul a vizionat mai mult de 1/3 din numărul total de episoade, dar mai puțin de
2/3: if_bored
                Dacă utilizatorul a vizionat mai puțin de 1/3 din numărul total de episoade: disliked
        :param id: Id-ul TvShow
        :param nr_eps_vizionate: numarul de episoade vizionate de utilizator
        :return: [tv_show, preferinta]
        :rtype: list of TvShow and str
        """
        show_cautat = self.__repo.cauta_dupa_ID(id)
        show_evaluation = ShowEvaluation(show_cautat, nr_eps_vizionate)
        return [show_cautat, show_evaluation.get_preference()]