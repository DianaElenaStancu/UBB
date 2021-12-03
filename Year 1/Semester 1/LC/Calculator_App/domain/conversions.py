import math
from domain.calculator import mul, sum, div

#conversia rapida
def convert_din_baza_2(a, baza):
    """
    Converteste rapid din baza 2 in baza 4, 8, 16
    :param a: numarul in baza 2
    :type a: string
    :return b: numarul convertit in baza 4, 8 sau 16
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

    #daca lungimea numarului nu este divizibila cu 2(daca baza = 4), 3(daca baza = 8) sau 4(daca baza = 16)
    #atunci adaugam zerouri la sfarsitul numarului
    len_gr = int(math.log2(baza))
    while len(a)%len_gr != 0:
        a = "0" + a

    #fiecare grupa de cifre are un corespondent in tabel, mai exact in dictionarele create mai sus
    for i in range(len_gr, len(a)+len_gr, len_gr):
        grupa = a[i-len_gr:i]
        if(baza == 4):
            b += dig_to_str[base_4.index(grupa)]
        elif(baza == 8):
            b += dig_to_str[base_8.index(grupa)]
        else:
            b += dig_to_str[base_16.index(grupa)]

    return b

def convert_in_baza_2(a, baza):
    """
    Converteste rapid din baza putere a lui 2: 4, 8, 16 in baza 2
    :param a: numarul in baza 4, 8, 16
    :type a: string
    :return b: numarul convertit in baza 2
    :rtype: string
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}

    base_4 = ["00","01","10","11"]
    base_8 = ["000", "001", "010","011","100","101","110","111"]
    base_16 = ["0000", "0001", "0010","0011","0100","0101","0110","0111", "1000","1001","1010","1011", "1100","1101","1110","1111"]

    b = ""

    #fiecare cifra are un corespondent in tabel, mai exact in listele initializate mai sus
    for i in range(0, len(a)):
        cifra =str_to_dig[a[i]]
        if baza == 4:
            b = b + base_4[cifra]
        elif baza == 8:
            b = b + base_8[cifra]
        else:
            b = b + base_16[cifra]

    #se elimina zerourile din fata sirului a
    while b[0] == '0' and len(b) != 1:
        b = b[1:]

    return b


def convert_rapid(a, baza_sursa, baza_destinatie):
    """
    Converteste rapid din baza_sursa putere a lui 2 in baza_destinatie tot putere a lui 2
    :param a: numarul citit de la tastatura
    :type a: string
    :param baza_sursa: baza sursa din care se doreste conversia
    :type: int
    :param baza_destinatie: baza destinatie in care se doreste conversia
    :type: int
    :return b: numarul convertit
    :rtype: str
    """
    if baza_destinatie == baza_sursa:
        return a

    if math.log2(baza_sursa) == 1:
        b = convert_din_baza_2(a, baza_destinatie)
    elif math.log2(baza_destinatie) == 1:
        b = convert_in_baza_2(a, baza_sursa)
    else:
        intermediar = convert_in_baza_2(a, baza_sursa)
        b = convert_din_baza_2(intermediar, baza_destinatie)

    return b


#conversia directa
def convert_impartiri(a, baza_sursa, baza_destinatie):
    """
    Converteste direct dintr-o baza in alta prin metoda impartirilor succesive
    :param a: numarul citit de la tastatura
    :type a: string
    :param baza_sursa: baza sursa din care se doreste conversia
    :type: int
    :param baza_destinatie: baza destinatie in care se doreste conversia
    :type: int
    :return b: numarul convertit
    :rtype: str

    Conditie: baza_sursa > baza_destinatie
    Metoda:
    calculele se efectueaza in baza baza_sursa
    numarul se imparete cu baza baza_destinatie si se va pastra atat catul, cat si restul
    catul se imparte cu baza baza_destinatie si se va pastra atat catul, cat si restul
    ....
    pana cand cat = 0
    la fiecare pas se adauga restul la b (concatenare de stringuri)
    """
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    b = ""
    rezultat_div = div(a, dig_to_str[baza_destinatie], baza_sursa)
    cat = rezultat_div[0]
    rest = rezultat_div[1]

    while cat != '0':
        b = rest + b
        a = cat
        rezultat_div = div(a, dig_to_str[baza_destinatie], baza_sursa)
        cat = rezultat_div[0]
        rest = rezultat_div[1]

    if rest != '0':
        b = rest + b

    return b

def convert_substitutie(a, baza_sursa, baza_destinatie):
    """
    Converteste direct dintr-o baza in alta prin metoda substitutiei
    :param a: numarul citit de la tastatura
    :type a: string
    :param baza_sursa: baza sursa din care se doreste conversia
    :type: int
    :param baza_destinatie: baza destinatie in care se doreste conversia
    :type: int
    :return b: numarul convertit
    :rtype: str

    Conditie: baza_sursa < baza_destinatie
    Metoda:
    calculele se efectueaza in baza baza_destinatie
    b = a[0]*baza_sursa^0 + a[1]*baza_sursa^1 + a[2]*baza_sursa^2+...+a[n]*baza_sursa^n
    unde numerotarea se va lua de la dreapta catre stanga
    """
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    putere = '1'
    b = '0'
    for i in range(len(a) - 1, -1, -1):
        cifra = a[i]
        # b = b + putere*cifra
        b = sum(b, mul(putere, cifra, baza_destinatie), baza_destinatie)
        #putere = putere*baza_sursa
        putere = mul(putere, dig_to_str[baza_sursa], baza_destinatie)
    return b


def convert_directa(a, baza_sursa, baza_destinatie):
    """
    Converteste direct dintr-o baza in alta
    :param a: numarul citit de la tastatura
    :type a: string
    :param baza_sursa: baza sursa din care se doreste conversia
    :type: int
    :param baza_destinatie: baza destinatie in care se doreste conversia
    :type: int
    :return b: numarul convertit
    :rtype: str
    """
    if baza_sursa == baza_destinatie:
        return a

    # se elimina zerourile din fata sirului a
    while a[0] == '0' and len(a) != 1:
        a = a[1:]

    #se va trece din baza mai mica in cea mare prin substitutie
    if baza_destinatie > baza_sursa:
        b = convert_substitutie(a, baza_sursa, baza_destinatie)
    else: #se va trece din baza mai mare in baza mai mica prin impartiri succesive
        b = convert_impartiri(a, baza_sursa, baza_destinatie)

    return b

#conversia utilizand baza intermediara 10
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
    Converteste din baza_sursa in baza_destinatie (2->16) cu baza intermediara 10
    :param a: numarul citit de la tastatura
    :type a: string
    :return baza_destinatie: baza destinatie in care se doreste conversia
    :rtype: string
    """
    if baza_sursa == baza_destinatie:
        return a

    #convertim prima data din baza_sursa in baza 10
    intermediar = convert_in_baza_10(a, baza_sursa)
    #convertim din baza 10 in baza sursa
    b = convert_din_baza_10(intermediar, baza_destinatie)
    return b






