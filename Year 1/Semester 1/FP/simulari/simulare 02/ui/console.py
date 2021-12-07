from repository.repofile import RepoException


class Console:
    def __init__(self, srv):
        self.__srv = srv
        self.__cmds = {
            "1": self.__ui_cauta_dupa_gen,
            "2": self.__ui_preferinte_utilizator
        }

    def run(self):
        exit = False
        while not exit:
            print("Comenzi disponibile: 0 - exit, 1 - cautare show dupa gen, 2 - returnare preferinta utilizator")
            cmd = input("Comanda este: ")
            if cmd in self.__cmds:
                self.__cmds[cmd]()
            elif cmd == "0":
                exit = True
            else:
                print("Comanda invalida")


    def __ui_cauta_dupa_gen(self):
        """citeste de la tastatura genul show-ului si tipareste show-urile disponibile
        pentru care genul contine stringul dat"""

        gen = input("Genul: ")
        if gen == "":
            print("Scrieti genul!")
            return
        show_cautate = self.__srv.cauta_dupa_gen(gen)
        for show in show_cautate:
            print(show)

    def __ui_preferinte_utilizator(self):
        """
        citeste de la tastatura id-ul si numarul de ore vizionate
        :return: -
        tipărește titlul serialului, genul
        din care face parte, și preferința utilizatorul
        """
        try:
            id = input("Id: ")
            nr_eps_vizionate = int(input("Numarul de episoade vizionate: "))
            show, preferinta = self.__srv.preferinte_utilizator(id, nr_eps_vizionate)
            print(show.getTitlu(), show.getGen(), preferinta)
        except ValueError as ve:
            print(str(ve))
        except RepoException as re:
            print(str(re))