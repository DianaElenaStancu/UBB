from domain.entities import Carte
from domain.validators import Validator
from utils.utils import existaCifra


class ServiceException(Exception):
    pass

class Service:
    def __init__(self, repository, validator):
        self.__repository = repository
        self.__validator = validator
        self.__filtru = ["", -1]

    #adauga carte
    def adaugaCarte(self, id, titlu, autor, anAparitie):
        """
        adauga carte
        :param id: id-ul cartii
        :param titlu: titlul cartii
        :param autor: autorul cartii
        :param anAparitie: an apartiei carte
        :return: cartea adaugata in lista
        :raise: ValidatorException daca cartea este invalida
        """
        carte = Carte(id, titlu, autor, anAparitie)
        self.__validator.valideazaCarte(carte)
        self.__repository.existaCarte(carte)
        self.__repository.store(carte)
        return carte

    #modifica carte
    """
    se da o cifra si un autor se modifica autorul pentru toate
    cartile pentru care id contine cifra data (modifica se vad imediat in fisier)
    """

    def cautaIdCuCifra(self, cifra):
        """
        functia cauta id-urile care contin cifra data
        returneaza lista de carti cu id-urile date
        """
        carti = self.getAll()
        cartiCautate = []
        for carte in carti:
            if existaCifra(carte.getId(), cifra):
                cartiCautate.append(carte)
        return cartiCautate

    def modificaAutor(self, cifra, autor):
        cartiCautate = self.cautaIdCuCifra(cifra)
        for carte in cartiCautate:
            self.__repository.modificaAutorCarte(carte, autor)

    def undo(self):
        self.__repository.undo()

    #filtru
    """
    aplicatia afiseaza filtru curent si lista cartilor (aplicand filtru curent)
    la pornire si dupa actionarea oricarui element de meniu. la afisare sunt incluse produsele
    care in titlu contin textul si au anul mai mic decat anul din filtru.
    """
    def modificaFiltru(self, text, an):
        self.__filtru[0] = text
        self.__filtru[1] = an

    def filtreazaCarti(self):
        text = self.__filtru[0]
        an =  self.__filtru[1]
        carti = self.__repository.getAll()
        cartiCautate = []
        if an == -1:
            return carti
        for carte in carti:
            if text in carte.getTitlu() and an > carte.getAnAparitie():
                cartiCautate.append(carte)
        return cartiCautate



    def getAll(self):
        return self.__repository.getAll()
