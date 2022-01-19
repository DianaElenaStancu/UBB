from domain.entities import Piesa

class RepositoryException(Exception):
    pass

class Repository:
    def __init__(self, filename):
        self.__filename = filename
        self.__piese = []
        self.__load_from_file()

    def __load_from_file(self):
        with open(self.__filename, 'r') as f:
            self.__piese = []
            for linie in f:
                linie.strip()
                try:
                    at = linie.split(";")
                    titlu = at[0]
                    regizor = at[1]
                    gen = at[2]
                    durata = int(at[3])
                    piesa = Piesa(titlu, regizor, gen, durata)
                    self.__piese.append(piesa)
                except:
                    continue

    def __save_to_file(self):
        with open(self.__filename, 'w') as f:
            for piesa in self.__piese:
                f.write(piesa.to_string())
                f.write("\n")

    def store(self, piesa):
        if piesa not in self.__piese:
            self.__piese.append(piesa)
            self.__save_to_file()
        else:
            raise RepositoryException("piesa existenta")

    def modifica(self, piesa_noua):
        if piesa_noua in self.__piese:
            self.__piese[self.__piese.index(piesa_noua)] = piesa_noua
            self.__save_to_file()

    def get_all(self):
        return self.__piese