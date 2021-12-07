class Service():
    def __init__(self, repo):
        self.__repo = repo


    def cauta_dupa_nume(self, sir_caractere):
        picturi = self.__repo.getAll()
        picturi_cautate = []
        for pictura in picturi:
            if sir_caractere.lower() in pictura.getNume().lower():
                picturi_cautate.append(pictura)
        return picturi_cautate

    def autori_si_pictura_noua(self):
        picturi = self.__repo.getAll()
        autori_dict = {}
        for pictura in picturi:
            if pictura.getNumeAutor() not in autori_dict or autori_dict[pictura.getNumeAutor()] < pictura.getAn():
                autori_dict[pictura.getNumeAutor()] = pictura.getAn()
        return autori_dict

