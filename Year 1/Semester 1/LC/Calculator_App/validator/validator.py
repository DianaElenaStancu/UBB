import math
def valideaza_numar(x, baza):
    """
        Se verifica daca numarul exista in baza respectiva sau nu
        :param x: numarul
        :type x: string
        :param baza: baza in care se afla numarul
        :tupe baza: int
        return: Ridica o eroare daca numarul introdus de utilizator este invalid
    """
    dig_str = "0123456789ABCDEF"

    lungime_x = len(x)
    if lungime_x == 0:
        raise ValueError("Introduceti un numar!")

    for i in range(0, lungime_x-1):
        if x[i] not in dig_str[:baza]:
            raise ValueError("Numarul introdus nu este din baza", baza)

def valideaza_cifra(x, baza):
    """
        Se verifica daca numarul introdus este de tip cifra si daca se afla in baza baza
        :param x: cifra
        :type x: string
        :param baza: baza in care se afla numarul
        :tupe baza: int
        return: Ridica o eroare daca numarul introdus de utilizator este invalid
    """
    dig_str = "0123456789ABCDEF"
    if len(x) > 1 or len(x) == 0:
        raise ValueError("Introduceti o cifra!")
    if x[0] not in dig_str[:baza]:
        raise ValueError("Cifra introdusa nu este din baza", baza)

def valideaza_baza(baza):
    """
        se verifica daca baza este corect introdusa
        :param baza: baza de numeratie
        :type baza: int
    """
    if not (baza >= 2 and baza <= 16):
        raise ValueError("Introduceti o baza de la 2 la 16")

def valideaza_convertire_rapida(baza_sursa, baza_destinatie):
    """
        se verifica daca se poate efectua conversia rapida de la baza_sursa la baza_destinatie
        :param baza_sursa: baza de numeratie din care se efectueaza conversia
        :type baza: int
        :param baza_destinatie: baza de numeratie in care se efectueaza conversia
        :type baza: int

    """
    valideaza_baza(baza_sursa)
    valideaza_baza(baza_destinatie)
    baza_sursa = int(baza_sursa)
    baza_destinatie = int(baza_destinatie)
    if not (math.log2(baza_sursa) == int(math.log2(baza_sursa)) and math.log2(baza_destinatie) == int(math.log2(baza_destinatie))):
        raise ValueError("Nu se poate efectua conversia rapida intre cele doua baze!")