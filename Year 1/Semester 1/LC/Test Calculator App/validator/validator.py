from Calculator_App.validator.validator import valideaza_numar, valideaza_baza, valideaza_cifra


def test_valideaza_numar():
    try:
        valideaza_numar("12345", 5)
        assert False
    except:
        assert True

    try:
        valideaza_numar("dsafasf", 2)
        assert False
    except:
        assert True

    valideaza_numar("1010100", 2)

    try:
        valideaza_numar("", 5)
        assert False
    except:
        assert True

def test_valideaza_cifra():
    try:
        valideaza_cifra("4", 2)
        assert False
    except:
        assert True

    try:
        valideaza_cifra("", 2)
        assert False
    except:
        assert True

    try:
        valideaza_cifra("dsafasf", 2)
        assert False
    except:
        assert True

    valideaza_cifra("0", 8)
    valideaza_cifra("F", 16)

def test_valideaza_baza():
    try:
        valideaza_baza(0)
        assert False
    except:
        assert True

    try:
        valideaza_baza(17)
        assert False
    except:
        assert True