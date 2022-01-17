from datetime import date, time
from domain.entities import Eveniment
from utils.conversii import conversieData, conversieTimp


class Service():
    def __init__(self, repo, val):
        self.__repo = repo
        self.__val = val

    """
    evenimente din ziua curenta ordonat dupa ora la care are loc
    evenimentul 
    """

    def getAllOrdered(self, data):
        evenimente = self.__repo.getAll()
        evenimenteAzi = []
        for e in evenimente:
            if data == e.getData():
                evenimenteAzi.append(e)
        evenimenteAzi = sorted(evenimenteAzi, key=lambda i: i.getOra())
        return evenimenteAzi

    def adaugaEveniment(self, data, ora, descriere):
        e = Eveniment(data, ora, descriere)
        self.__val.valideazaEveniment(e)
        data = conversieData(data)
        ora = conversieTimp(ora)
        evenimentDeAdaugat = Eveniment(data, ora, descriere)
        self.__repo.store(evenimentDeAdaugat)
        return evenimentDeAdaugat

    def cautaEvenimenteText(self, text):
        evenimente = self.__repo.getAll()
        evenimenteCautate = []
        for e in evenimente:
            if text in e.getDescriere():
                evenimenteCautate.append(e)
        evenimenteCautate = sorted(evenimenteCautate, key = lambda e: [e.getData(), e.getOra()])
        return evenimenteCautate