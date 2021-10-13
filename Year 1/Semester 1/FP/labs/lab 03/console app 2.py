"""
Scrieti o aplicatie care are interfata utilizator tip consolă cu un meniu:
1 Citirea unei liste de numere intregi
2 Se cauta secventa de lungime maximă cu proprietatea ca contine cel mult trei valori distincte (2)
3 Se cauta secventa de lungime maximă cu proprietatea ca sunt toate distincte intre ele(6)
4 Se cauta secventa de lungime maximă cu proprietatea ca oricare doua elemente consecutive sunt relativ prime intre ele (a, b relativ prime daca si numai daca cmmdc(a,b) = 1). (3)
5 Iesire din aplicatie.

Documentatia să contină:
 Scenarii de rulare pentru cele două cerinte primite (vezi curs 1 – scenarii de rulare)
 Cazuri de testare pentru cele doua cerinte în format tabelar (vezi curs 1 – cazuri de testare)
"""

from termcolor import colored

def print_menu():
    """
    Functia afiseaza meniul aplicatiei
    """
    print(colored("\n**************", 'yellow'))
    print("Meniul aplicatiei: ")
    print("1 Citirea unei liste de numere intregi.")
    print("2 Se cauta secventa de lungime maximă cu proprietatea ca contine cel mult trei valori distincte")
    print("3 Se cauta secventa de lungime maximă cu proprietatea ca sunt toate distincte intre ele")
    print("4 Iesire din aplicatie")
    print(colored("**************\n", 'yellow'))


def populate_list(the_list):
    """
    Functia populeaza lista data cu o serie de numere intregi predefinite
    :param the_list: lista data
    :type the_list: list
    :return:  -; lista se modifica, continand la final elementele adaugate
    :rtype:
    """
    the_list.append(-7)
    the_list.append(8)
    the_list.append(7)
    the_list.append(4)
    the_list.append(-89)
    the_list.append(4)
    the_list.append(-7)
    the_list.append(10)
    the_list.append(23)
    the_list.append(56)
    the_list.append(10)

def read_list():
    """
    Functia citeste si prelucreaza lista de numere introduse de utilizator.
    :param: -
    :type: -
    :return: lista citita
    :rtype: list
    """
    #format: 7, -8, 9, 123
    the_list_as_string = input(colored("Introduceti lista de numere intregi in formatul cerut: ", 'yellow'))
    list_of_strings = the_list_as_string.split(",")
    try:
        number_list = [float(elem.strip()) for elem in list_of_strings]
        return number_list
    except:
        exception()
        return read_list()


def max_seq_3_distinct_values(the_list):
    """
    Functia cauta secventa de lungime maxima cu proprietatea ca contine cel mult 3 valori distincte
    :param the_list: lista curenta
    :type the_list: list
    :return max_list: secventa de lungime maxima cu proprietatea ceruta
    :rtype: list
    """
    the_list_len = len(the_list)
    max_list = []

    if the_list_len <= 3:
        max_list = the_list
    else:
        for it1 in range(0, the_list_len - 2):
            distinct_values_list = []
            it2 = it1
            while len(distinct_values_list) <= 3 and it2 < the_list_len:
                if the_list[it2] not in distinct_values_list:
                    distinct_values_list.append(the_list[it2])
                it2 = it2 + 1

            if len(distinct_values_list) > 3:
                it2 = it2 - 1

            if it2 - it1 > len(max_list):
                max_list = the_list[it1:it2]

    return max_list

# set

def max_seq_with_distinct_values(the_list):
    """
    Functia returneaza secventa de lungime maxima cu proprietatea ca sunt toate distincte intre ele
    :param the_list: lista curenta
    :type the_list: list
    :return max_list: secventa de lungime maxima cu proprietatea ceruta
    :rtype list
    """
    the_list_len = len(the_list)
    max_list = []

    if len(the_list)== 1:
        max_list = the_list
    else:
        for it1 in range(0, the_list_len - 1):
            it2 = it1 + 1
            while it2 < the_list_len and the_list[it2] not in the_list[it1:it2]:
                it2 = it2 + 1
            if it2 - it1 > len(max_list):
                max_list = the_list[it1:it2]

    return max_list

def cmmdc(a, b):
    while(a != b):
        if a > b:
            a = a - b
        else:
            b = b - a
    return a

def max_seq_with_relative_prime_numbers(the_list):
    """
    Functia returneaza secventa de lungime maxima cu proprietatea ca oricare doua elemente consecutive sunt relativ prime intre ele (a, b relativ prime daca si numai daca cmmdc(a,b) = 1).
    :param the_list: lista curenta
    :type the_list: list
    :return max_list: secventa de lungime maxima cu proprietatea ceruta
    :rtype list
    """
    the_list_len = len(the_list)
    max_list = []
    if len(the_list)== 1:
        max_list = the_list
    else:
        for it1 in range(0, the_list_len - 1):
            it2 = it1 + 1
            prec = the_list[it1]
            act = the_list[it2]
            while prec > 0 and act > 0 and cmmdc(prec, act) == 1 and prec != act:
                it2 = it2 + 1
                prec = act
                if it2 < the_list_len:
                    act = the_list[it2]
                else:
                    break
            if it2 - it1 > len(max_list):
                max_list = the_list[it1:it2]

    return max_list


def exception():
    print(colored("**************", 'red'))
    print(colored("Invalid input", 'red'))
    print(colored("**************", 'red'))

def test_max_seq_3_distinct_values():
    assert max_seq_3_distinct_values([1, 1, 1, 2, 3, 3, 4, 5, 6]) == [1, 1, 1, 2, 3, 3]
    assert max_seq_3_distinct_values([1, 2, 3, 3, 4, 5, 6]) == [1, 2, 3, 3]
    assert max_seq_3_distinct_values([1, 2]) == [1, 2]
    assert max_seq_3_distinct_values([9, 9, 9, 9, 9, 9, 9, 9]) == [9, 9, 9, 9, 9, 9, 9, 9]
    assert max_seq_3_distinct_values([1, 2, 3, 4, 5, 5, 5, 5, 5, 5]) == [3, 4, 5, 5, 5, 5, 5, 5]
    assert max_seq_3_distinct_values([1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 2, 3]
    assert max_seq_3_distinct_values([1]) == [1]
    print("Tests passed option 2 :)")

def test_max_seq_with_distinct_values():
    assert max_seq_with_distinct_values([1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 2, 3, 4, 5, 6, 7, 8, 9]
    assert max_seq_with_distinct_values([1, 1, 1, 1, 2, 2, 2, 3, 4, 4]) == [2, 3, 4]
    assert max_seq_with_distinct_values([1, 1, 1, 1, 1, 1, 1, 1, 1]) == [1]
    assert max_seq_with_distinct_values([1, 2, 2, 3, 3, 4, 5, 5, 5, 6, 7, 8, 8]) == [5, 6, 7, 8]
    assert max_seq_with_distinct_values([1, 2, 2, 3, 3, 4, 4, 5, 5, 6]) == [1, 2]
    assert max_seq_with_distinct_values([1]) == [1]
    print("Tests passed option 3 :)")

def test_max_seq_with_relative_prime_numbers():
    assert max_seq_with_relative_prime_numbers([1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 2, 3, 4, 5, 6, 7, 8, 9]
    assert max_seq_with_relative_prime_numbers([1, 1, 1, 1, 2, 2, 2, 3, 4, 4]) == [2, 3, 4]
    assert max_seq_with_relative_prime_numbers([1, 1, 1, 1, 1, 1, 1, 1, 1]) == [1]
    assert max_seq_with_relative_prime_numbers([1, 2, 2, 3, 3, 4, 5, 5, 5, 6, 7, 8, 8]) == [5, 6, 7, 8]
    assert max_seq_with_relative_prime_numbers([1, 2, 2, 3, 3, 4, 4, 5, 5, 6]) == [1, 2]
    assert max_seq_with_relative_prime_numbers([1]) == [1]
    print("Tests passed option 4 :)")

def start():
    current_list = []
    populate_list(current_list)
    while True:
        print_menu()
        print(colored("Lista cu numere intregi: ", 'green'), colored(current_list, 'green'))
        option = input(colored("Optiunea dumneavoastra este: ", 'yellow'))
        if option == '1':
            current_list = read_list()
        elif option == '2':
            print(colored("Secventa de lungime maximă cu proprietatea ca contine cel mult trei valori distincte este: ", 'magenta'), max_seq_3_distinct_values(current_list))
        elif option == '3':
            print(colored("Secventa de lungime maximă cu proprietatea ca sunt toate distincte intre ele este: ",'magenta'), max_seq_with_distinct_values(current_list))
        elif option == '4':
            print(colored("Oricare doua elemente consecutive sunt relativ prime intre ele ",'magenta'), max_seq_with_relative_prime_numbers(current_list))
        elif option == '5':
            print(colored("Bye bye!", 'magenta'))
            return
        else:
            exception()


test_max_seq_3_distinct_values()
test_max_seq_with_distinct_values()
test_max_seq_with_relative_prime_numbers()
start()