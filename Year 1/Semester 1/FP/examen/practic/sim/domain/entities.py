class Piesa:
    def __init__(self, titlu, regizor, gen, durata):
        self.__titlu = titlu
        self.__regizor = regizor
        self.__gen = gen
        self.__durata = durata

    def get_titlu(self):
        return self.__titlu
    def get_regizor(self):
        return self.__regizor
    def get_gen(self):
        return self.__gen
    def get_durata(self):
        return self.__durata

    def set_gen(self, value):
        self.__gen = value

    def set_gen(self, durata):
        self.__gen = durata

    def __eq__(self, other):
        return self.__titlu == other.get_titlu() and self.__regizor == other.get_regizor()

    def to_string(self):
        return self.__titlu + ";" +  self.__regizor + ";" + self.__gen + ";" + str(self.__durata)