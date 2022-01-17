class Service:
    def __init__(self, repository):
        self.__repository = repository

    #cerinta 1
    def cautaDupaDescriere(self, substring):
        """
        Functia creeaza o lista de buguri ale caror descriere au in componenta sa substringul substring, apoi
        sorteaza lista descrescator dupa prioritate
        :param substring: sir de caractere care trebuie cautat in descrierea fiecarui bug
        :type substring: str
        :return: lista de bug-uri cu proprietatea ceruta ordonate descrescator dupa prioritate
        :rtype: list of Bug(s)
        """
        bugs = self.__repository.getAll()
        bugs_cautate = []
        for bug in bugs:
            if substring in bug.getDescriere():
                bugs_cautate.append(bug)
        bugs_sortate = sorted(bugs_cautate, key = lambda bug: bug.getPrioritate(), reverse = True)
        return bugs_sortate


    #cerinta 2
    @staticmethod
    def calculeazaMedia(list):
        """
        calculeaza media elementelor intregi ale unei liste
        :param list: lista de numere intregi
        :return: media
        :rtype: float
        """
        sum = 0
        for el in list:
            sum += el
        return sum/len(list)


    def mediePrioritati(self):
        """
        Functia creeaza un dict format din componenta afectata si media prioritatilor bugurilor aferente
        :return: dictionarul creat
        :rtype: dict key = componenta_afectata, value = media_prioritati
        """
        bugs = self.__repository.getAll()
        #key = componenta_afectata, value = [prioritate1, prioritate2, ....]
        components_and_priorities_list = {}
        for bug in bugs:
            if bug.getComponentaAfectata() not in components_and_priorities_list:
                components_and_priorities_list[bug.getComponentaAfectata()] = [bug.getPrioritate()]
            else:
                components_and_priorities_list[bug.getComponentaAfectata()].append(bug.getPrioritate())

        #in final facem media prioritatilor
        #key = componenta_afectata, value = media_prioritati
        components_and_average = {}
        for componenta, prioritati_list in components_and_priorities_list.items():
            medie = self.calculeazaMedia(prioritati_list)
            components_and_average[componenta] = medie
        return components_and_average
