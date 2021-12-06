class Console:
    def __init__(self, srv):
        self.__srv = srv
        self.__comenzi = {
            "1": self.__ui_FindByScope,
            "2":self.__ui_getAllScopes
        }



    def __ui_FindByScope(self):
        """
        citeste de la tastatura scopul pentru care trebuie afisata lista de elicoptere
        """
        scop = input("Scopul: ")
        if scop == "" :
            print("Scrieti scopul!")
            return
        lista = self.__srv.findByScope(scop)
        for elicopter in lista:
            print(elicopter)

    def __ui_getAllScopes(self):
        """
        pentru fiecare scop distinct, se afișează anii de fabricație ale elicopterelor care se pot folosi cu scopul respectiv
        """
        scopuri_dict = self.__srv.getAllScopes()
        for scope, ani in scopuri_dict.items():
            raspuns = " -   " + scope  + ": " + ", ".join(ani)
            print(raspuns)



    def run(self):
        exit = False
        while not exit:
            print("Comenzi disponibile: 0 - exit, 1 - Afișarea tuturor elicopterelor care conțin un anumit scop, 2 - Grupare după scopuri")
            cmd = input("Comanda este: ")
            if cmd == '0':
                exit = True
            elif cmd in self.__comenzi:
                self.__comenzi[cmd]()
            else:
                print("Comnda invalida")

