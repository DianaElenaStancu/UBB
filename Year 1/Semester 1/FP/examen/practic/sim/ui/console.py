class Console:
    def __init__(self, srv):
        self.__srv = srv
        self.__cmds = {
            "1": self.__afiseaza,
            "2": self.__store,
            "3": self.__modifica
        }

    def run(self):
        exit = False
        while not exit:
            cmd = input("comanda: ")
            if cmd == '0':
                exit = True
            elif cmd in self.__cmds:
                self.__cmds[cmd]()
            else:
                print("comanda invalida")

    def __afiseaza(self):
        piese = self.__srv.get_all()
        for piesa in piese:
            print(piesa.to_string())

    def __store(self):
        try:
            titlu = input("titlu: ")
            regizor = input("regizor: ")
            gen = input("gen: ")
            durata = int(input("durata: "))
            self.__srv.store(titlu, regizor, gen, durata)
        except Exception as e:
            print(str(e))

    def __modifica(self):
        try:
            titlu = input("titlu: ")
            regizor = input("regizor: ")
            gen = input("gen: ")
            durata = int(input("durata: "))
            self.__srv.modifica(titlu, regizor, gen, durata)
        except Exception as e:
            print(str(e))