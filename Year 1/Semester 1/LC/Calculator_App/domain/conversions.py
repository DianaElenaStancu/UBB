import math
from domain.calculator import mul, sum

def convert_2_to_power_of_2(a, baza):
    """
    Converteste rapid din baza 2 in baza 4, 8, 16
    :param a: numarul citit de la tastatura
    :type a: string
    :return b: numarul in baza 8
    :rtype: string
    """
    base_4 = ["00","01","10","11"]
    base_8 = ["000", "001", "010","011","100","101","110","111"]
    base_16 = ["0000", "0001", "0010","0011","0100","0101","0110","0111", "1000","1001","1010","1011", "1100","1101","1110","1111"]
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    b = ""
    #se elimina zerourile din fata sirului a
    while a[0] == '0' and len(a) != 1:
        a = a[1:]

    #daca lungimea numarului nu este divizibila cu 3 atunci adaugam zerouri la sfarsitul numarului
    #pentru a putea grupa numarul in grupe de cate 3
    len_gr = int(math.log2(baza))
    while len(a)%len_gr != 0:
        a = "0" + a

    for i in range(len_gr, len(a)+len_gr, len_gr):
        grupa = a[i-len_gr:i]
        if(baza == 4):
            b += dig_to_str[base_4.index(grupa)]#two_to_4[grupa]
        elif(baza == 8):
            b += dig_to_str[base_8.index(grupa)]#two_to_8[grupa]
        else:
            b += dig_to_str[base_16.index(grupa)]#two_to_16[grupa]

    return b

def convert_power_of_2_to_2(a, baza):
    """
        Converteste rapid din baza 2 in baza 4, 8, 16
        :param a: numarul citit de la tastatura
        :type a: string
        :return b: numarul in baza 8
        :rtype: string
    """
    pass

def convert_directa(a, baza_sursa, baza_destinatie):
    """
        Converteste direct dintr-o baza in alta
        :param a: numarul citit de la tastatura
        :type a: string
        :param baza_sursa: baza sursa din care se doreste conversia
        :type: string
        :param baza_destinatie: baza destinatie in care se doreste conversia
        :type: string
        :return b: numarul convertit
        :rtype: str
    """
    b = ""
    # se elimina zerourile din fata sirului a
    while a[0] == '0' and len(a) != 1:
        a = a[1:]

    #se va trece din baza mai mica in cea mare prin substitutie
    if baza_destinatie > baza_sursa:
        str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                      'C': 12, 'D': 13, 'E': 14, 'F': 15}
        putere = '1'
        b = '0'
        print(a)
        for i in range(len(a) - 1, -1, -1):
            cifra = a[i]
            print("in conv: ", type(a[i]))
            b = sum(b, mul(putere, cifra, baza_destinatie), baza_destinatie)
            putere = mul(putere, baza_sursa, baza_destinatie)
    return b


def test_convert_directa():
    print("*******************")
    print(convert_directa("1332", 5, 9))





def convert_din_baza_10(a, baza_destinatie):
    """
        Converteste prin metoda impartirilor succesive din baza_sursa 10 in baza_destinatie (2->16)
        :param a: numarul citit de la tastatura
        :type a: string
        :param baza_destinatie: baza destinatie in care se doreste conversia
        :type: string
        :return b: numarul convertit
        :rtype: str
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}

    b = ""
    #se elimina zerourile din fata sirului a
    while a[0] == '0' and len(a) != 1:
        a = a[1:]

    a = int(a)
    cat = a//baza_destinatie
    rest = a%baza_destinatie

    while cat != 0:
        b = dig_to_str[rest] + b
        a = cat
        cat = a // baza_destinatie
        rest = a % baza_destinatie

    if rest != 0:
        b = dig_to_str[rest] + b

    return b

def convert_in_baza_10(a, baza_sursa):
    """
        Converteste dintr-o baza_sursa in baza 10
        :param a: numarul citit de la tastatura
        :type a: string
        :return baza_sursa: baza sursa din care se doreste conversia
        :rtype: string
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}
    putere = 1
    b = 0
    for i in range (len(a) - 1, -1, -1):
        b = b + putere*str_to_dig[a[i]]
        putere = putere*baza_sursa

    b = str(b)

    return b

def convert_intermediar(a, baza_sursa, baza_destinatie):
    """
        Converteste prin substitutie din baza_sursa in baza_destinatie (2->16) cu baza intermediara 10
        :param a: numarul citit de la tastatura
        :type a: string
        :return baza_destinatie: baza destinatie in care se doreste conversia
        :rtype: string
    """
    #convertim prima data din baza_sursa in baza 10
    intermediar = convert_in_baza_10(a, baza_sursa)
    #convertim din baza 10 in baza sursa
    b = convert_din_baza_10(intermediar, baza_destinatie)
    return b

def test_convert_intermediar():
    pass





