from domain.entities import Product
from domain.validators import ProductValidator
from repository.product_repo import InMemoryRepository

class ProductService:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_product(self, denumire, stoc, pret):
        """
        :raises: Value Error daca produsul e invalid
        :param denumire:
        :param stoc:
        :param pret:
        :return:
        """
        product = Product(denumire, stoc, pret)
        self.__validator.validate(product)
        self.__repo.store(product)

    def get_all_products(self):
        return self.__repo.get_all_products()

def test_add_product():
    test_repo = InMemoryRepository()
    test_val = ProductValidator()

    test_srv = ProductService(test_repo, test_val)

    product = test_srv.add_product('jeleuri', 33, 1.25)
    assert(product.getName() == 'jeleuri')
    assert(product.getStoc() == 33)
    assert(len(test_srv.get_all_products()) == 1)