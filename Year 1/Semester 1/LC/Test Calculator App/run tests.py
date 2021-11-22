from domain.calculator import test_sum, test_dif, test_mul, test_div
from validator.validator import test_valideaza_numar, test_valideaza_cifra, test_valideaza_baza
from domain.conversions import test_convert_2_to_4_8_16, test_convert_clasic, test_convert_baza_10


def run():
    test_sum()
    test_dif()
    test_mul()
    test_div()
    test_valideaza_numar()
    test_valideaza_cifra()
    test_valideaza_baza()
    test_convert_2_to_4_8_16()
    test_convert_clasic()
    test_convert_baza_10()

    print("tests passed :)")

run()