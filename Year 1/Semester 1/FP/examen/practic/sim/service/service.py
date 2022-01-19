from domain.entities import Piesa


class Service:
    def __init__(self, repo, val):
        self.__repo = repo
        self.__val = val

    def get_all(self):
        return self.__repo.get_all()

    def store(self, titlu, regizor, gen, durata):
        piesa_noua = Piesa(titlu, regizor, gen, durata)
        self.__val.valideaza_piesa(piesa_noua)
        self.__repo.store(piesa_noua)

    def modifica(self, titlu, regizor, gen, durata):
        piesa_noua = Piesa(titlu, regizor, gen, durata)
        self.__val.valideaza_piesa(piesa_noua)
        self.__repo.modifica(piesa_noua)