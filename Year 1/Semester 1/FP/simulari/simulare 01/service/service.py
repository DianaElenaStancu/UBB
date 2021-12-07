class Service:
    def __init__(self, repo):
        self.__repo = repo

    #1 returneaza lista elicopterelor care conțin un anumit scop citit de la tastatură în șirul cu
    #scopuri, ordonate descrescător după nume
    def findByScope(self, scop):
        """
        returneaza lista elicopterelor care contin un anumite scop citit de la
        tastatura ordinate descrescator dupa nume
        :param scop: scopul elicopterului
        :type scop: str
        :return: lista de elicoptere cu proprietatile cerute
        :rtype: list of Elicopter
        """
        elicoptere = self.__repo.getAll()
        elicoptere_cautate = []
        for elicopter in elicoptere:
            scopuri = elicopter.getScopuri()
            if scop in scopuri:
                elicoptere_cautate.append(elicopter)
        elicoptere_sortate = sorted(elicoptere_cautate, key = lambda elicopter: elicopter.getNume(), reverse=True)
        return elicoptere_sortate

    #2. Grupare după scopuri: pentru fiecare scop distinct, se afișează anii de fabricație ale
    # elicopterelor care se pot folosi cu scopul respectiv
    def getAllScopes(self):
        """
        :return: un dictionar cu toate scopurile si lista de ani de fabricatie a
        elicopterelor care au acel scop
        :rtype: dict
        exemplu: {"agricultură": [2014],
        "medical": [2014, 1995]
        "vacanță": [2014]
        "militar": [1995, 2019]
        "livrare": [2019]}
        """
        elicoptere = self.__repo.getAll()
        scopuri_dict = {}
        for elicopter in elicoptere:
            scopuri = elicopter.getScopuri()
            anFabricatie = elicopter.getAnFabricatie()
            scopuri_lista = scopuri.split(" ")
            for scop in scopuri_lista:
                if scop not in scopuri_dict:
                    scopuri_dict[scop] = [str(anFabricatie)]
                elif str(anFabricatie) not in scopuri_dict[scop]:
                    scopuri_dict[scop].append(str(anFabricatie))
        return scopuri_dict




