from domain.calculator import test_sum, test_dif, test_mul, test_div
from validator.validator import test_valideaza_numar, test_valideaza_cifra, test_valideaza_baza
from domain.conversions import test_convert_din_baza_2, test_convert_in_baza_2, test_convert_rapid, test_convert_directa,\
    test_convert_impartiri, test_convert_substitutie, test_convert_din_baza_10, test_convert_in_baza_10, test_convert_intermediar

def run():
    test_sum()
    test_dif()
    test_mul()
    test_div()
    test_valideaza_numar()
    test_valideaza_cifra()
    test_valideaza_baza()
    test_convert_din_baza_2()
    test_convert_in_baza_2()
    test_convert_rapid()
    test_convert_impartiri()
    test_convert_substitutie()
    test_convert_directa()
    test_convert_din_baza_10()
    test_convert_in_baza_10()
    test_convert_intermediar()
    print("tests passed :)")

run()