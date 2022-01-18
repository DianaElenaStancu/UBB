from domain.entities import Produs


class Service:
    def __init__(self, repository, validator):
        self.__repository = repository
        self.__validator = validator
        self.__filtru = ["", -1]

    def store(self, id, denumire, pret):
        produs = Produs(id, denumire, pret)
        self.__validator.valideazaProdus(produs)
        produs = Produs(int(id), denumire, int(pret))
        self.__repository.store(produs)
        return produs


    def delete(self, cifra):
        produseDeSters = self.__repository.cautaDupaPret(cifra)
        self.__repository.delete(produseDeSters)
        return len(produseDeSters)

    def setFiltru(self, text, pret):
        self.__filtru = [text, pret]

    def filtrare(self):
        text = self.__filtru[0]
        pret = self.__filtru[1]
        if pret == -1:
            return self.__repository.getAll()
        produseCautate = []
        produse = self.__repository.getAll()
        for p in produse:
            if text in p.getDenumire() and p.getPret() < pret:
                produseCautate.append(p)
        return produseCautate

    def undo(self):
        self.__repository.undo()