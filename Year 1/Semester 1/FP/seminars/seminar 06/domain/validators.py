from domain.entities import Product

class Validation_Exception(Exception):
    pass

class ProductValidator:
    def validate(self, product):
        errors = []
        if product.getName() == '':
            errors.append("Denumirea produsului nu poate fi vida.")
        if product.getStoc() < 0:
            errors.append("Numarul de unitati din stoc nu poate fi negativ.")
        if product.getPret() < 0:
            errors.append("Pretul nu poate fi negativ")

        if len(errors) > 0:
            error_string  = '\n'.join(errors)
            raise ValueError(error_string)
            #raise Validation Exception

#o clasa este un tip de data propriu pe care il definim noi,
#iar obiectul = instanta unei clase
#clasa telefon, tipul telefon care are anumite atribute
#obiectele sunt lucrurile specifice: telefonul tau, al meu, etc

def test_validate_product():
    validator = ProductValidator() #am creat un obiect de tipul ProductValidator
    p1 = Product('jeleuri', 10, 12.5)
    validator.validate(p1)

    p1 = Product('', -10, 12.5)
    try:
        validator.validate(p1)
        assert False
    except ValueError: #in cazul in care primim eroare sa treaca testul
        assert True

    p2 = Product('acadele', 6, -4)
    try:
        validator.validate(p2)
        assert False
    except ValueError: #in cazul in care primim eroare sa treaca testul
        assert True