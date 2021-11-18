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

def test_sum():
    assert (sum('1', '1', 2) == '10')
    assert (sum('101101001', '1001111', 2) == '110111000')
    assert (sum('12210012', '2211', 3) == '12220000')
    assert (sum('12332132', '213321233', 4) == '232320031')
    assert (sum('1233213442', '2144334241233', 5) == '2201123010230')
    assert (sum('33335554', '555', 6) == '33340553')
    assert (sum('227625', '10000000', 8) == '10227625')
    assert (sum('12345678', '8888765432100', 9) == '8888777777778')
    assert (sum('2052', '779', 10) == '2831')
    assert (sum('454369', 'A5436', 11) == '5497A4')
    assert (sum('4543B6900', 'A5436', 12) == '4544A0136')
    assert (sum('99999', 'BBAB450', 13) == 'BC78119')
    assert (sum('99999', 'BBAB450', 14) == 'BC67009')
    assert (sum('99999', 'BBAB450', 15) == 'BC55DE9')
    assert (sum('99999', 'BBAB450', 16) == 'BC44DE9')

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

def test_dif():
    assert(dif('101000', '1111', 2) == '11001')
    assert (dif('12221000', '12201200', 3) == '12100')
    assert (dif('123321010', '23', 4) == '123320321')
    assert (dif('234432', '20032', 5) == '214400')
    assert (dif('132455', '5555', 6) == '122500')
    assert (dif('54321', '3456', 7) == '50532')
    assert (dif('3000', '677', 8) == '2101')
    assert (dif('1101', '1101', 9) == '0')
    assert (dif('12345', '2345', 10) == '10000')
    assert (dif('AAAA', '9999', 11) == '1111')
    assert (dif('ABAB', '9889', 12) == '1322')
    assert (dif('ABC0AB', '567', 13) == 'ABB844')
    assert (dif('CC000', '199A', 14) == 'CA444')
    assert (dif('134896A', '722BCD', 15) == 'B25C8C')
    assert (dif('EEEEE', '98744', 16) == '567AA')

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

    for i in range(len(a) - 1, -1, -1):
        valoare_curenta = (str_to_dig[a[i]]*str_to_dig[c]+transport)%baza
        transport = (str_to_dig[a[i]] * str_to_dig[c] + transport) // baza
        produs = dig_to_str[valoare_curenta] + produs

    if transport > 0:
        produs = dig_to_str[transport] + produs

    return produs

def test_mul():
    assert(mul('9', '2', 10) == '18')


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

def test_div():
    assert (div("1221", "2", 3) == ["222", "0"])
    assert (div("122130", "3", 4) == ["20310", "0"])
    assert (div("122130", "4", 5) == ["14131", "1"])
    assert (div("54321", "3", 6) == ["15304", "1"])
    assert (div("14131", "3", 7) == ["3510", "1"])
    assert (div("3510", "7", 8) == ["412", "2"])
    assert (div("653635840", "5", 9) == ["127842880", "0"])
    assert (div("99123450", "1", 10) == ["99123450", "0"])
    assert (div("99AA123450", "9", 11) == ["1112388A30", "0"])
    assert (div("99AA123B45", "6", 12) == ["17798247A8", "5"])
    assert (div("17798247A", "8", 13) == ["276103A9", "3"])
    assert (div("C5D45", "7", 14) == ["1ABC8", "5"])
    assert (div("1345", "A", 15) == ["1C6", "5"])
    assert (div("1CD", "E", 16) == ["20", "D"])


