import math
def convert_2_to_4_8_16(a, baza):
    """
    Converteste rapid din baza 2 in baza 8
    :param a: numarul citit de la tastatura
    :type a: string
    :return b: numarul in baza 8
    :rtype: string
    """
    two_to_4 = {"00": "0","01": "1","10": "2","11": "3"}
    two_to_8 = {"000": "0", "001": "1", "010": "2","011": "3","100": "4","101": "5","110": "6","111": "7"}
    two_to_16 = {"0000": "0", "0001": "1", "0010": "2","0011": "3","0100": "4","0101": "5","0110": "6","0111": "7", "1000":"8","1001": "9","1010": "A","1011": "B", "1100": "C","1101": "D","1110": "E","1111": "F"}
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
            b += two_to_4[grupa]
        elif(baza == 8):
            b += two_to_8[grupa]
        else:
            b += two_to_16[grupa]

    return b

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





