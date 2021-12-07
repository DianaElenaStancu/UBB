class Console():
    def __init__(self, srv):
        self.__srv = srv
        self.__cmds = {
            "1": self.__ui_cauta_dupa_nume,
            "2": self.__autori_si_pictura_noua
        }

    def run(self):
        exit = False
        while not exit:
            print("Comenzi disponibile: 0 - exit, 1 - cauta dupa nume, 2 - lista autori si cea mai noua pictura")
            cmd = input("Comanda este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == '0':
                exit = True
            else:
                print("Comanda invalida!")

    def __ui_cauta_dupa_nume(self):
        sir_caractere = input("Sir de caractere: ")
        picturi_cautate = self.__srv.cauta_dupa_nume(sir_caractere)
        for pictura in picturi_cautate:
            print(pictura)

    def __autori_si_pictura_noua(self):
        autori_dict = self.__srv.autori_si_pictura_noua()
        for autor, pictura in autori_dict.items():
            print(autor,": ", pictura)