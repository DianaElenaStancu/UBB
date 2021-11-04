class InMemoryRepository:
    def __init__(self):
        self.__products = []

    #adauga in lista
    def store(self, product):
        self.__products.append(product)
    #sterge din lista
    #modifica element din lista
    #cauta element in lista

    def get_all_products(self):
        return self.__products