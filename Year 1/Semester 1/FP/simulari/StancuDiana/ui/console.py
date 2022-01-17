from repository.repository import RepoException


class Console:
    def __init__(self, service):
        self.__srv = service
        self.__cmds = {
            "1": self.__cautaDupaDescriere_ui,
            "2": self.__mediePrioritati_ui
        }

    @staticmethod
    def __printMenu():
        print("Comenzi: ")
        print("0 - exit")
        print(
            "1 - Afișarea tuturor bugurilor care conțin în descriere un șir de caractere citit de la tastatură, ordonate descrescător după prioritate")
        print("2 - Afisarea listei de componente afectate si media prioritatilor lor")

    def run(self):
        exit = False
        while not exit:
            self.__printMenu()
            cmd = input("Comanda este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda invalida")

    def __cautaDupaDescriere_ui(self):
        """
        citeste de la tastatura un substring dat de utilizator si afiseaza
        bugurile care conțin în descriere acest substring, ordonate descrescător după prioritate
        :return: -
        """
        substring = input("Sirul de caractere: ")
        if substring == "":
            print("Scrieti un sir de caractere valid!")
            return
        try:
            bugs = self.__srv.cautaDupaDescriere(substring)
            if len(bugs) == 0:
                print("Lista goala :(")
            else:
                for bug in bugs:
                    print(bug)
        except RepoException as re:
            print(str(re))

    def __mediePrioritati_ui(self):
        """
        Afiseaza lista de componente afectate si media prioritatilor lor
        :return: -
        """
        bugs = self.__srv.mediePrioritati()
        if len(bugs) == 0:
            print("Nimic de afisat :(")
        else:
            for componenta, medie in bugs.items():
                print(" - ", componenta, ": ", medie)
