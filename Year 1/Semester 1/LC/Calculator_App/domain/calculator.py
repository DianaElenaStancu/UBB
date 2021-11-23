#suma a doua numere
def sum(a, b, baza):
    """
    calculeaza suma a+b in baza baza
    :param a: primul numar
    :type a: string
    :param b: al doilea numar
    :type b: string
    :param baza: baza in care se va face suma
    :return: suma celor doua numere a si b
    :rtype: string
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15}
    dig_to_str = {0:'0', 1:'1', 2:'2', 3:'3', 4:'4', 5:'5', 6: '6', 7:'7', 8:'8', 9:'9', 10: 'A', 11:'B', 12:'C', 13:'D', 14:'E', 15:'F'}

    lungime_a = len(a)
    lungime_b = len(b)

    string_0 = ""
    sum = ""

    dif_len = abs(lungime_a - lungime_b)

    #numerele a si b trebuie sa fie de aceeasi lungime
    #pentru a face acest lucru voi crea un string: string_0
    #string_0 = "000....0", unde lungimea lui string_0 este egala cu dif
    for i in range(0, dif_len):
        string_0 += "0"

    #se adauga string_0 in fata numarului mai mic
    #astfel incat cele doua numere sa aiba lungimea egala
    if (lungime_a < lungime_b):
        a = string_0 + a
    else:
        b = string_0 + b

    #setam transportul la 0
    transport = 0

    # algoritmul de adunare a doua numere intr-o baza oarecare
    # lungimea maxima pe care o poate avea suma celor doua numere
    lungime_max = max(lungime_a, lungime_b) + 1
    for i in range(lungime_max - 2, -1, -1):
        valoare_curenta = transport + str_to_dig[a[i]]+ str_to_dig[b[i]]

        # actualizam transportul
        transport = valoare_curenta // baza

        # valoarea curenta este restul impartirii valorii la baza
        valoare_curenta = valoare_curenta % baza

        # actualizam suma
        sum = dig_to_str[valoare_curenta] + sum

    if (transport > 0):
        sum = dig_to_str[transport] + sum

    return sum

#diferenta a doua numere
def dif(a, b, baza):
    """
    preconditie a>=b
    calculeaza diferenta a-b in baza baza
    :param a: primul numar
    :type a: string
    :param b: al doilea numar
    :type b: string
    :param baza: baza in care se va face diferenta
    :return: diferenta celor doua numere a si b
    :rtype: string
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}

    lungime_a = len(a)
    lungime_b = len(b)

    string_0 = ""
    dif = ""

    dif_len = abs(lungime_a - lungime_b)

    # numerele a si b trebuie sa fie de aceeasi lungime
    # pentru a face acest lucru voi crea un string: string_0
    # string_0 = "000....0", unde lungimea lui string_0 este egala cu dif
    for i in range(0, dif_len):
        string_0 += "0"

    # se adauga string_0 in fata numarului mai mic
    # astfel incat cele doua numere sa aiba lungimea egala
    if (lungime_a < lungime_b):
        a = string_0 + a
    else:
        b = string_0 + b

    #setam transportul
    transport = 0
    # algoritmul de adunare a doua numere intr-o baza oarecare
    # lungimea maxima pe care o poate avea suma celor doua numere
    lungime_max = max(lungime_a, lungime_b)
    for i in range(lungime_max - 1, -1, -1):
        if str_to_dig[a[i]] + transport >= str_to_dig[b[i]]:
            valoare_curenta = str_to_dig[a[i]] + transport - str_to_dig[b[i]]
            transport = 0
        else:
            valoare_curenta = baza + str_to_dig[a[i]] + transport - str_to_dig[b[i]]
            transport = -1
        dif = dig_to_str[valoare_curenta] + dif

    #eliminam 0-urile din fata daca sunt
    while dif[0] == '0' and len(dif) != 1:
        dif = dif[1:]
    return dif

#inmultirea unui numar cu o cifra
def mul(a, c, baza):
    """
    calculeaza a*c in baza b
    :param a: numar
    :type a: string
    :param c: o cifra
    :type c: string
    :param baza: baza in care se va face inmultirea
    :return: a*c
    :rtype: string
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}

    produs = ""
    transport = 0
    print("in calc: ", type(c))
    for i in range(len(a) - 1, -1, -1):
        valoare_curenta = (str_to_dig[a[i]]*str_to_dig[c]+transport)%baza
        transport = (str_to_dig[a[i]] * str_to_dig[c] + transport) // baza
        produs = dig_to_str[valoare_curenta] + produs

    if transport > 0:
        produs = dig_to_str[transport] + produs

    #eliminam 0-urile din fata daca sunt
    while produs[0] == '0' and len(produs) != 1:
        produs = produs[1:]

    return produs

#impartirea unui numar la o cifra
def div(a, c, baza):
    """
    calculeaza catul a//c si restul a%c
    :param a: numar
    :type a: string
    :param c: o cifra
    :type c: string
    :param baza: baza in care se va face inmultirea
    :return: [a//c, a%c]
    :rtype: list of stringa

    observatie: a//c = [a/c] - impartire intreaga
    """
    str_to_dig = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, 'A': 10, 'B': 11,
                  'C': 12, 'D': 13, 'E': 14, 'F': 15}
    dig_to_str = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9', 10: 'A', 11: 'B',
                  12: 'C', 13: 'D', 14: 'E', 15: 'F'}
    cat = ""
    rest = ""
    transport = 0
    for i in range(0, len(a)):
        valoare_curenta = (transport*baza+str_to_dig[a[i]])//str_to_dig[c]
        transport = (transport*baza+str_to_dig[a[i]])%str_to_dig[c]
        cat = cat + dig_to_str[valoare_curenta]
    rest = dig_to_str[transport]
    #eliminam 0-urile din fata daca sunt
    while cat[0] == '0' and len(cat) != 1:
        cat = cat[1:]
    return [cat, rest]


