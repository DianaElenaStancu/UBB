from domain.entities import Product


class InMemoryRepository:
    """
    metodele CRUD:create, update, delete
    """
    def __init__(self):
        self.__products = []

    #adauga in lista
    def find(self, id):
        """
        cauta un produs cu id-ul dat in lista
        :param id:  id-ul dat
        :type id: str
        :return: produsul cu id-ul dat, None daca nu exista produs cu id-ul cautat
        :rtype: Product
        """
        for product in self.__products:
            if product.getId() == id:
                return product
        return None

    def store(self, product):
        p = self.find(product.getId())
        if p is not None:
            raise ValueError('Produsul cu acest id exista deja')

        self.__products.append(product)
    #sterge din lista
    #modifica element din lista
    #cauta element in lista

    def get_all_products(self):
        return self.__products

    def size(self):
        return len(self.__products)

    def __find_index(self, id):
        """
        gaseste indezul pozitia produsului cu identificator id in lista
        :param id:  id dat
        :return: index-ul produsului cu id id in lista
        """
        index = -1
        for i in range(self.size()):
            if self.__products[i].getId() == id:
                index = i
                break
        return index

    def delete_product(self, id):
        """
        sterge produsul cu if dat
        :param id: id-ul dat
        :return:
        """
        """
        product = self.find(id)
        if product is None:
            raise ValueError("Nu exista produs cu id-ul dat")
        self.__products.remove(product)
        return product  
        """
        index = self.__find_index(id)
        if index == -1:
            raise ValueError("Id inexistent")
        return self.__products.pop(index)
        #remove(value)-elimina primul cu valoarea value
        #pop(index) sau doar pop()-elimina ultimul element
        #del lista[index]

    #def update_

def test_store():
    test_repo = InMemoryRepository()
    p1 = Product('1', 'jeleuri', 10, 12.5)
    p2 = Product('2', 'jeleuri', 10, 12.5)
    test_repo.store(p1)
    assert (len(test_repo()) == 1)
    test_repo.store(p2)
    assert (len(test_store()) == 2)

    try:
        p1 = Product('1', 'jeleuri', 10, 12.5)
        assert False
    except:
        assert True

def test_delete_by_id():
    test_repo = InMemoryRepository()
    p1 = Product('1', 'jeleuri', 10, 12.5)
    p2 = Product('2', 'jeleuri', 12, 8.5)
    test_repo.store(p1)
    test_repo.store(p2)

    deleted_p = test_repo.delete_product('1')
    assert (deleted_p.getName() == 'jeleuri')
    assert(deleted_p.getPret() == 12.5)
    assert (deleted_p.getStoc() == 10)

    try:
        deleted_p = test_repo.delete_product('hdasoigda')
        assert False
    except:
        assert True


