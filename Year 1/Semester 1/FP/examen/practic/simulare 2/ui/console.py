from datetime import date

from domain.validator import ValidatorException
from utils.conversii import conversieData


class Console():
    def __init__(self, srv):
        self.__srv = srv
        self.__cmds = {
            "1": self.__afiseazaEvenimente,
            "2": self.__adaugaEveniment,
            "3": self.__schimbaData,
            "4": self.__export
        }

    def __printMenu(self):
        print("Comenzile disponibile: ")
        print("0 - exit")
        print("1 - afiseaza evenimente")
        print("2 - adauga eveniment")
        print("3 - schimba data")
        print("4 - export")

    def run(self):
        exit = False
        self.__afiseazaEvenimente()
        while not exit:
            self.__printMenu()
            cmd = input("Comanda ta este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda invalida")

    def __schimbaData(self):
        data = input("data noua: ")
        try:
            data = conversieData(data)
            self.__afiseazaEvenimente(data)
        except Exception as e:
            print(str(e))


    def __afiseazaEvenimente(self, data = date.today()):
        evenimente = self.__srv.getAllOrdered(data)
        for e in evenimente:
            print(e.to_string())

    def __adaugaEveniment(self):
        try:
            data = input("data: ")
            ora = input("ora: ")
            descriere = input("descriere: ")
            self.__srv.adaugaEveniment(data, ora, descriere)
        except ValidatorException as ve:
            print(str(ve))
            return

    def __export(self):
        numeFisier = input("nume fisier: ")
        text = input("text: ")
        with open(numeFisier, 'w') as f:
            evenimente = self.__srv.cautaEvenimenteText(text)
            for e in evenimente:
                f.write(e.to_string())
                f.write('\n')


