"""
P6. AGENȚIE DE TURISM
Creați o aplicație pentru gestiunea pachetelor de călătorie oferite de o agenție de
turism. Aplicația stochează pachete de călătorie oferite clienților după cum
urmează: data de început și cea de sfârșit a călătoriei, destinația și prețul.

Aplicația va permite:
    1. Adăugare
        • Adaugă pachet de călătorie
        • Modifică pachet de călătorie
    2. Ștergere
        • Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată
        • Ștergerea tuturor pachetelor de călătorie care au o durată mai scurtă decât un număr de zile dat
        • Ștergerea tuturor pachetelor de călătorie care au prețul mai mare decât o sumă dată
    3. Căutare
        • Tipărirea pachetelor de călătorie care presupun un sejur într-un interval dat (e.g. 10/08/2018 - 24/08/2018 -
        un pachet valid este cel a cărui dată de început este aceeași sau după de data de început citită și data de
         sfârșit este înainte sau aceeași cu data de sfârșit introdusă de la tastatură)
        • Tipărirea pachetelor de călătorie cu o destinație dată și cu preț mai mic decât o sumă dată.
        • Tipărirea pachetelor de călătorie cu o anumită dată de sfârșit
    4. Rapoarte
        • Tipărirea numărului de oferte pentru o destinație dată.
        • Tipărirea tuturor pachetelor disponibile într-o anumită perioadă citită de la tastatură (vezi 3.i.) în
        ordinea crescătoare a prețului.
        • Tipărirea mediei de preț pentru o destinație dată
    5. Filtrare
        • Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la
        tastatură
        • Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună (citită de la tastatură sub forma
        unui număr natural între 1 și 12)
    6. Undo
        • Refacerea ultimei operații (lista de oferte revine la ce exista înainte de ultima operație care a modificat
        lista) – Nu folosiți funcția deepCopy
"""
from termcolor import colored
from datetime import date

def generate_pockets():
    return [[date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 1200], [date(2021, 11, 20), date(2021,11,30), 'Paris', 1500],
            [date(2022, 8, 10), date(2022, 8, 17), 'Dubai', 1600], [date(2022, 3, 3), date(2022, 3, 8), 'Paris', 900],
            [date(2022, 1, 1), date(2022, 2, 1), 'Constanta', 1000], [date(2022, 4, 8), date(2022, 4, 11), 'Viena', 500]]

def create_pocket(start_date, finish_date, destination, price):
    """
    Creeaza un pachet de calatorie cu atributele date
    :param start_date: data de inceput a calatoriei
    :type start_date: date
    :param finish_date: data la care se incheie calatoria
    :type finish_date: date
    :param destination: destinatia calatoriei
    :type destination: string
    :param price: pretul calatoriei
    :type price: int
    :return: pachetul de calatorie
    :rtype: list (len(lst) = 4, lst[0] = start_date, lst[1] = finish_date, lst[2] = destination, lst[3] = price)
    """
    return [start_date, finish_date, destination, price]

def get_start_date(pocket):
    return pocket[0]

def get_finish_date(pocket):
    return pocket[1]

def get_destination(pocket):
    return pocket[2]

def get_price(pocket):
    return pocket[3]

def valid_period(start_date, finish_date):
    """
    :param start_date:
    :type start_date: date
    :param finish_date:
    :type finish_date: date
    :return: true if the start_date is before the finish_date and false in the contrary case
    :rtype: bool
    """
    if (finish_date-start_date).days > 0:
        return True
    return False

def add_pocket_to_list(lst, pocket):
    """
    Adauga la lista de pachete un nou pachet de calatorie
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param pocket: pachetul de calatorie introdus de utilizator
    :type pocket: list
    :return: -; modifica lista prin adaugarea noului element
    """
    lst.append(pocket)

def remove_pocket_with_destination(lst, destination):
    """
    Sterge toate pachetele care au o anumita destinatie
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param destination: destinatia data de utilizator
    :type destination: string
    :return lst: lista de pachete de calatorii modificata
    :rtype lst: list (of lists)
    """
    new_list = [pocket for pocket in lst if get_destination(pocket).lower() != destination.lower()]
    return new_list

def remove_pocket_with_smaller_duration(lst, duration):
    """
    Sterge toate pachetele care au durata de zile mai mica decat cea data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param duration: durata in zile introdusa de utilizator
    :type duration: int
    :return lst: lista de pachete de calatorii modificata
    :rtype lst: lista
    """
    new_list = []
    for pocket in lst:
        if (get_finish_date(pocket) - get_start_date(pocket)).days >= duration:
            new_list.append(pocket)
    return new_list

def remove_pocket_with_greater_price(lst, price):
    """
    Sterge toate pachetele care au pretul mai mare decat o suma data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param price: suma introdusa de utilizator
    :type price: int
    :return lst: lista de pachete de calatorii modificata
    :rtype lst: list (of lists)
    """
    new_list = [pocket for pocket in lst if get_price(pocket) <= price]
    return new_list

def fits_in_the_period(given_start_date, given_finish_date, pocket_start_date, pocket_finish_date):
    """
    Functia determina daca intervalul calendaristic [given_start_date, given_finish_date]
    este inclus in intervalul [pocket_start_date, pocket_finish_date]
    (e.g. 10/08/2018 - 24/08/2018 -
        un pachet valid este cel a cărui dată de început este aceeași sau după de data de început citită și data de
         sfârșit este înainte sau aceeași cu data de sfârșit introdusă de la tastatură)
    :param given_start_date: data de inceput a intervallui calendaristic introdus de utilizator
    :param given_finish_date:data de sfarsit a intervallui calendaristic introdus de utilizator
    :param pocket_start_date: data de inceput a intervalului calendaristic din pachet
    :param pocket_finish_date:data de sfarsit a intervalului calendaristic din pachet
    :return: adevarat daca [given_start_date, given_finish_date] este
    inclus in/egal cu [pocket_start_date, pocket_finish_date], fals in caz contrar
    """
    if given_start_date >= pocket_start_date and given_finish_date <= pocket_finish_date:
        return True
    return False

def nr_pockets_with_given_destination(lst, destination):
    """
    Returneaza numarul de pachete care au o destinatie data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param destination: destinatia introdusa de utilizator
    :type destination: string
    :return nr_pockets: numarul de pachete cu destinatia data
    :rtype: int
    """
    nr_pockets = 0
    for pocket in lst:
        if get_destination(pocket).lower() == destination.lower():
            nr_pockets += 1
    return nr_pockets

def average_price_of_pockets_with_given_destination(lst, destination):
    """
    Returneaza media de pret a ofertelor de calatorie cu destinatia data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :param destination: destinatia calatoriei
    :type destination: string
    :return avg_price: pretul mediu
    :rtype avg_price: float
    """
    nr_pockets = 0
    sum_price = 0
    for pocket in lst:
        if get_destination(pocket).lower() == destination.lower():
            nr_pockets += 1
            sum_price += get_price(pocket)
    if nr_pockets != 0:
        return sum_price/nr_pockets
    return 0

def sort_by_price(pocket):
    return get_price(pocket)

def ordered_pockets_by_price_with_given_destination(lst, start_date, finish_date):
    """
    Returneaza lista de pachete de calatorie incadrate in intervalul start_date - finish_date in ordinea pretului
    :param lst: lista de pachete de calatorie
    :type lst: list(of lists)
    :param start_date: data de inceput a calatoriei
    :type start_date: date
    :param finish_date:data de sfarsit a calatoriei
    :type finish_date: date
    :return new_list: lista de pachete de calatorie incadrate in intervalul start_date - finish_date in ordinea pretului
    :rtype new_list: list (of lists)
    """
    new_list = []
    for pocket in lst:
        if fits_in_the_period(start_date, finish_date, get_start_date(pocket), get_finish_date(pocket)):
            new_list.append(pocket)
    new_list.sort(key=sort_by_price)
    return new_list

#INTERFACE FUNCTIONS
def exception():
    print(colored('\n**********************************', 'red'))
    print(colored('INPUT INVALID', 'red'))
    print(colored('**********************************\n', 'red'))

def print_menu():
    print(colored('\n**********************************', 'yellow'))
    print(colored('Adăugare', 'magenta'))
    print('1. Adaugă pachet de călătorie')
    print('2. Modifică pachet de călătorie')
    print(colored('Stergere', 'magenta'))
    print('3. Șterge pachetele de călătorie disponibile pentru o destinație dată')
    print('4. Șterge pachetele de călătorie care au o durată mai scurtă decât un număr de zile dat')
    print('5. Șterge pachetele de călătorie care au prețul mai mare decât o sumă dată')
    print(colored('Cautare', 'magenta'))
    print('6. Tipăreste pachetele de călătorie care presupun un sejur într-un interval dat')
    print('7. Tipăreste pachetele de călătorie cu o destinație dată și cu preț mai mic decât o sumă dată')
    print('8. Tipăreste pachetele de călătorie cu o anumită dată de sfârșit')
    print(colored('Rapoarte', 'magenta'))
    print('9. Tipăreste numărul de oferte pentru o destinație dată.')
    print('10. Tipăreste pachetele disponibile într-o anumită perioadă citită de la tastatură în ordinea crescătoare a prețului.')
    print('11. Tipăreste media de preț pentru o destinație dată.')
    print(colored('Alte functionalitati', 'magenta'))
    print('P Afișează lista de pachete de călătorie')
    print('X Închide aplicația')
    print(colored('**********************************\n', 'yellow'))

def print_pocket(nr, lst):
    print("Nr pachet: ", nr+1, "| Data de inceput:", get_start_date(lst[nr]), "| Data de sfarsit:", get_finish_date(
        lst[nr]), "| Destinatie:", get_destination(lst[nr]), "| Pret:", get_price(lst[nr]))

def print_pocket_list(lst):
    print(colored('\n**********************************', 'yellow'))
    print("Lista pachetelor de calatorie este formata din: ")
    lst_len = len(lst)
    if(lst_len == 0):
            print("Lista este goala")
    else:
        for nr in range(0, lst_len):
            print_pocket(nr, lst)
    print(colored('**********************************\n', 'yellow'))

def read_date():
    """
    Citeste de la tastatura o data calendaristica
    :return: data
    :rtype: date
    """
    validInput = False

    while not validInput:
        date_year = input(colored("-> Anul: ", 'yellow'))
        date_month = input(colored("-> Luna: ", 'yellow'))
        date_day = input(colored("-> Ziua: ", 'yellow'))
        try:
            return date(int(date_year), int(date_month), int(date_day))
        except ValueError:
            exception()

def read_price():
    """
    :return: pretul calatoriei
    :rtype: int
    """
    try:
        price = int(input(colored("Pretul calatoriei: ", 'yellow')))
    except ValueError:
        exception()
        return read_price()
    return price

def read_destination():
    """
        :return: destinatia calatoriei
        :rtype: string
    """
    try:
        destination = input(colored("Destinatia calatoriei: ", 'yellow'))
    except ValueError:
        exception()
        return read_destination()
    return destination

def read_pocket_number(lst):
    """
        :return: numarul pachetului
        :rtype: int
    """
    try:
        pocket_number = int(input(colored("Numarul pachetului pe care vrei sa il modifici: ", 'yellow')))
    except ValueError:
        exception()
        return read_pocket_number(lst)

    if pocket_number > len(lst) or pocket_number < 1:
        exception()
        return read_pocket_number(lst)
    return pocket_number

def read_duration():
    """
    Citeste numarul de zile introdus de utilizator
    :return duration: numarul de zile
    :rtype: int
    """
    try:
        duration = int(input(colored("Durata in zile: ", 'yellow')))
    except ValueError:
        exception()
        return read_duration()
    return duration

def add_pocket_ui(lst):
    print(colored("Data la care incepe calatoria: ", 'yellow'))
    start_date = read_date()
    print(colored("Data la care se sfarseste calatoria: ", 'yellow'))
    finish_date = read_date()

    while not valid_period(start_date, finish_date):
        exception()
        print(colored("Data la care incepe calatoria: ", 'yellow'))
        start_date = read_date()
        print(colored("Data la care se sfarseste calatoria: ", 'yellow'))
        finish_date = read_date()

    destination = read_destination()
    price = read_price()
    pocket = [start_date, finish_date, destination, price]
    add_pocket_to_list(lst, pocket)

def print_change_pocket_menu():
    print(colored('\n**********************************', 'yellow'))
    print('S Modifica data in care incepe calatoria')
    print('F Modifica data in care se incheie calatoria')
    print('D Modifică destinatia calatoriei')
    print('P Modifica pretul calatoriei')
    print('X Incheie procesul de modificare')
    print(colored('**********************************\n', 'yellow'))

def change_pocket_ui(lst):
    print_pocket_list(lst)
    pocket_number = read_pocket_number(lst)
    pocket_number -= 1
    print("Pachetul pe care il vei modifica este: ")
    print_pocket(pocket_number,lst)
    finished = False
    while not finished:
        print_change_pocket_menu()
        option = input(colored("Optiunea este: ", 'yellow'))
        if option.lower() == 's':
            lst[pocket_number][0] = read_date()
        elif option.lower() == 'f':
            lst[pocket_number][1] = read_date()
        elif option.lower() == 'd':
            lst[pocket_number][2] = read_destination()
        elif option.lower() == 'p':
            lst[pocket_number][3] = read_price()
        elif option.lower() == 'x':
            finished = True
        else:
            exception()
        if not valid_period(get_start_date(lst[pocket_number]), get_finish_date(lst[pocket_number])):
            print(colored("Trebuie sa modifici intervalul calatoriei pentru ca nu este valid", 'red'))
            finished = False

def remove_pocket_with_destination_ui(lst):
    """
    :param lst: lista de pachete de calatorii
    :type lst: list (of lists)
    :return lst: lista modificata
    :rtype lst: list (of lists)
    """
    destination = read_destination()
    lst = remove_pocket_with_destination(lst, destination)
    return lst

def remove_pocket_with_smaller_duration_ui(lst):
    """
    :param lst: lista de pachete de calatorii
    :type lst: list (of lists)
    :return lst: lista modificata
    :rtype lst: list (of lists)
    """
    duration = read_duration()
    lst = remove_pocket_with_smaller_duration(lst, duration)
    return lst

def remove_pocket_with_greater_price_ui(lst):
    """
        :param lst: lista de pachete de calatorii
        :type lst: list (of lists)
        :return lst: lista modificata
        :rtype lst: list (of lists)
        """
    price = read_price()
    lst = remove_pocket_with_greater_price(lst, price)
    return lst

def print_pockets_with_given_period_ui(lst):
    """
    Citeste data de inceput si data de sfarsit a intervalului intordus de utilizator
    si afiseaza elementele din lista care au sejurul in intervalul dat
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :return:-
    """
    print("Data de inceput a sejurului:")
    start_date = read_date()
    print("Data de sfarsit a sejurului:")
    finish_date = read_date()
    while(not valid_period(start_date, finish_date)):
        exception()
        print("Data de inceput a sejurului:")
        start_date = read_date()
        print("Data de sfarsit a sejurului:")
        finish_date = read_date()

    exist_pocket = 0
    print(colored('\n**********************************', 'yellow'))
    for pocket_nr in range(0, len(lst)):
        if fits_in_the_period(start_date, finish_date, get_start_date(lst[pocket_nr]), get_finish_date(lst[pocket_nr])) == True:
            exist_pocket = 1
            print_pocket(pocket_nr, lst)
    if not exist_pocket:
        print("Nu exista pachete :(")
    print(colored('**********************************\n', 'yellow'))

def print_pockets_with_given_destination_lower_price_ui(lst):
    """
    Citeste destinatia si pretul introduse de utilizator
    si afiseaza pachetele de calatorie care au destinatia data si pretul mai mic decat cel dat
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :return: -
    """
    destination = read_destination()
    price = read_price()
    exist_pocket = 0
    print(colored('\n**********************************', 'yellow'))
    for pocket_nr in range(0, len(lst)):
        if get_destination(lst[pocket_nr]) == destination and get_price(lst[pocket_nr]) < price:
            print_pocket(pocket_nr, lst)
            exist_pocket = 1
    if not exist_pocket:
        print("Nu exista pachete :(")
    print(colored('**********************************\n', 'yellow'))

def print_pockets_with_given_finish_date(lst):
    """
    Citeste data calendaristica de sfarsit a sejurului
    si afiseaza pachetele de calatorie care se termina in acea data
    :param lst: lista de pachete
    :type lst: list (of lists)
    :return: -
    """
    print("Data de sfarsit: ")
    finish_date = read_date()
    exist_pocket = 0
    print(colored('\n**********************************', 'yellow'))
    for pocket_nr in range(0, len(lst)):
        if get_finish_date(lst[pocket_nr]) == finish_date:
            print_pocket(pocket_nr, lst)
            exist_pocket = 1
    if not exist_pocket:
        print("Nu exista pachete :(")
    print(colored('**********************************\n', 'yellow'))

def print_number_of_pockets_with_destination(lst):
    """
    Citeste destinatia si afiseaza numarul de pachete care au destinatia data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :return:-;
    """
    destination = read_destination()
    nr_pockets = nr_pockets_with_given_destination(lst, destination)
    print("Numarul pachetelor care au destinatia", destination, "este", nr_pockets)

def print_average_price_of_pockets_with_given_destination(lst):
    """
    Citeste destinatia de la tastatura si afiseaza pretul mediu al ofertelor cu destinatia data
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :return:-
    """
    destination = read_destination()
    average_price = average_price_of_pockets_with_given_destination(lst, destination)
    print("Pretul mediu al pachetelor de calatorie cu destinatia data este:", average_price)

def print_pockets_in_order_with_given_period(lst):
    """
    Afiseaza lista de pachete de calatorie disponibile într-o anumită perioadă in ordinea crescatoare a pretului
    :param lst: lista de pachete de calatorie
    :type lst: list (of lists)
    :return: -
    """
    print("Data de inceput a sejurului:")
    start_date = read_date()
    print("Data de sfarsit a sejurului:")
    finish_date = read_date()
    while not valid_period(start_date, finish_date):
        exception()
        print("Data de inceput a sejurului:")
        start_date = read_date()
        print("Data de sfarsit a sejurului:")
        finish_date = read_date()
    new_list = ordered_pockets_by_price_with_given_destination(lst, start_date, finish_date)
    for pocket_number in range(0, len(new_list)):
        print_pocket(pocket_number, new_list)

#START FUNCTION
def start():
    crt_pocket_list = generate_pockets()
    finished = False
    while not finished:
        print_menu()
        option = input(colored('Optiunea este: ', 'yellow'))
        if option == '1':
            add_pocket_ui(crt_pocket_list)
            print(colored('Adaugarea pachetului a fost efectuata cu succes', 'yellow'))
        elif option == '2':
            change_pocket_ui(crt_pocket_list)
            print(colored('Modificarea pachetului a fost efectuata cu succes', 'yellow'))
        elif option  == '3':
            crt_pocket_list = remove_pocket_with_destination_ui(crt_pocket_list)
            print(colored(
                'Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată efectuata cu succes',
                'yellow'))
        elif option == '4':
            crt_pocket_list = remove_pocket_with_smaller_duration_ui(crt_pocket_list)
            print(colored(
                'Ștergerea tuturor pachetelor de călătorie care au o durată mai scurtă decât un număr de zile dat',
                'yellow'))
        elif option  == '5':
            crt_pocket_list = remove_pocket_with_greater_price_ui(crt_pocket_list)
            print(colored(
                'Ștergerea tuturor pachetelor de călătorie care au prețul mai mare decât o sumă dată',
                'yellow'))
        elif option == '6':
            print_pockets_with_given_period_ui(crt_pocket_list)
        elif option == '7':
            print_pockets_with_given_destination_lower_price_ui(crt_pocket_list)
        elif option == '8':
            print_pockets_with_given_finish_date(crt_pocket_list)
        elif option == '9':
            print_number_of_pockets_with_destination(crt_pocket_list)
        elif option == '10':
            print_pockets_in_order_with_given_period(crt_pocket_list)
        elif option == '11':
            print_average_price_of_pockets_with_given_destination(crt_pocket_list)
        elif option.lower() == 'p':
            print_pocket_list(crt_pocket_list)
        elif option.lower() == 'x':
            print(colored('Bye bye!', 'magenta'))
            finished = True
        else:
            exception()

#TESTS
def test_create_pocket():
    pocket = create_pocket(date(2021, 10, 21), date(2021, 10, 31), 'Zurich', 1100)
    assert(type(pocket) == list)
    assert(get_start_date(pocket).day == 21)
    assert (get_start_date(pocket).month == 10)
    assert (get_start_date(pocket).year == 2021)
    assert (get_finish_date(pocket).day == 31)
    assert (get_finish_date(pocket).month == 10)
    assert (get_finish_date(pocket).year == 2021)
    assert (get_destination(pocket) == 'Zurich')
    assert (get_price(pocket) == 1100)
    print("test_create_pocket passed")
    #cazurile cu input gresit trateaza-le!!

def test_add_pocket_to_list():
    test_list = []
    pocket1 = [date(2022, 10, 1), date(2022, 10, 12), 'New York', 1000]
    pocket2 = [date(2023, 11, 3), date(2023, 11, 10), 'Tokyo', 2400]

    add_pocket_to_list(test_list, pocket1)
    assert(len(test_list)==1)
    assert(get_start_date(test_list[0]).day == 1)
    assert(get_start_date(test_list[0]).month == 10)
    assert(get_start_date(test_list[0]).year == 2022)
    assert(get_finish_date(test_list[0]).day == 12)
    assert(get_finish_date(test_list[0]).month == 10)
    assert(get_finish_date(test_list[0]).year == 2022)
    assert(get_destination(test_list[0]) == 'New York')
    assert (get_price(test_list[0]) == 1000)

    add_pocket_to_list(test_list, pocket2)
    assert (len(test_list) == 2)
    assert (get_start_date(test_list[0]).day == 1)
    assert (get_start_date(test_list[0]).month == 10)
    assert (get_start_date(test_list[0]).year == 2022)
    assert (get_finish_date(test_list[0]).day == 12)
    assert (get_finish_date(test_list[0]).month == 10)
    assert (get_finish_date(test_list[0]).year == 2022)
    assert (get_destination(test_list[0]) == 'New York')
    assert (get_price(test_list[0]) == 1000)

    assert (get_start_date(test_list[1]).day == 3)
    assert (get_start_date(test_list[1]).month == 11)
    assert (get_start_date(test_list[1]).year == 2023)
    assert (get_finish_date(test_list[1]).day == 10)
    assert (get_finish_date(test_list[1]).month == 11)
    assert (get_finish_date(test_list[1]).year == 2023)
    assert (get_destination(test_list[1]) == 'Tokyo')
    assert (get_price(test_list[1]) == 2400)

    print("test_add_pocket_to_list passed")

def test_valid_period():
    assert(valid_period(date(2022, 10, 12), date(2022, 10, 20)) == True)
    assert(valid_period(date(2022, 10, 12), date(2022, 10, 12)) == False)
    assert (valid_period(date(2022, 10, 12), date(2022, 10, 2)) == False)
    assert (valid_period(date(2022, 10, 12), date(2022, 9, 20)) == False)
    assert (valid_period(date(2022, 10, 12), date(2020, 10, 20)) == False)
    print("test_valid_period passed")

def test_remove_pocket_with_destination():
    test_list1 = generate_pockets()
    init_len = len(test_list1)
    destination_test = 'Paris'
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)

    assert(len(test_list1) == init_len - 2)
    assert(len([pocket for pocket in test_list1 if get_destination(pocket) == destination_test]) == 0)
    init_len = len(test_list1)

    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert(len(test_list1) == init_len)

    destination_test = 'Brasov'
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert(len(test_list1) == init_len)

    test_list2 = []
    test_list2 = remove_pocket_with_destination(test_list2, destination_test)
    assert (len(test_list2) == 0)

    destination_test = ''
    test_list1 = remove_pocket_with_destination(test_list1, destination_test)
    assert (len(test_list1) == init_len)
    test_list2 = remove_pocket_with_destination(test_list2, destination_test)
    assert (len(test_list2) == 0)

    print("test_remove_pocket_with_destination passed")

def test_remove_pocket_with_smaller_duration():
    test_list1 = generate_pockets()
    duration = 7
    init_len = len(test_list1)
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert(len(test_list1) == init_len - 2)
    duration = 30
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert(len(test_list1) == 1)
    duration = 31
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 1)
    duration = 32
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 0)
    test_list1 = remove_pocket_with_smaller_duration(test_list1, duration)
    assert (len(test_list1) == 0)
    print("test_remove_pocket_with_smaller_duration passed")

def test_remove_pocket_with_greater_price():
    test_list = generate_pockets()
    init_len = len(test_list)
    price = 1500
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert(len(test_list) == init_len - 1)
    price = 1000
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert (len(test_list) == init_len - 4)
    price = 0
    test_list = remove_pocket_with_greater_price(test_list, price)
    assert (len(test_list) == 0)
    print("test_remove_pocket_with_greater_price passed")

def test_fits_in_the_period():
    assert(fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 13), date(2021, 10, 30)) == False)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 10), date(2021, 10, 20)) == True)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 9, 1), date(2021, 11, 1)) == True)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 9, 1), date(2021, 10, 9)) == False)
    assert (fits_in_the_period(date(2021, 10, 10), date(2021, 10, 20), date(2021, 10, 14), date(2021, 10, 19)) == False)
    print("test_fits_in_the_period passed")

def test_nr_pockets_with_given_destination():
    test_list = generate_pockets()
    assert(nr_pockets_with_given_destination(test_list, 'paris') == 2)
    assert (nr_pockets_with_given_destination(test_list, 'tenerife') == 1)
    assert (nr_pockets_with_given_destination(test_list, 'viena') == 1)
    assert (nr_pockets_with_given_destination(test_list, 'praga') == 0)
    test_list = []
    assert (nr_pockets_with_given_destination(test_list, 'kiev') == 0)
    print("test_nr_pockets_with_given_destination passed")

def test_average_price_of_pockets_with_given_destination():
    test_list = generate_pockets()
    assert(average_price_of_pockets_with_given_destination(test_list, 'paris') == 1200)
    assert(average_price_of_pockets_with_given_destination(test_list, 'viena') == 500)
    assert(average_price_of_pockets_with_given_destination(test_list, 'london') == 0)
    test_list.append([date(2021, 11, 20), date(2021,11,30), 'Paris', 229])
    assert (average_price_of_pockets_with_given_destination(test_list, 'paris') == 2629/3)
    print("test_average_price_of_pockets_with_given_destination")

def test_ordered_pockets_by_price_with_given_destination():
    test_list = generate_pockets()
    test_list.append([date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 2400])
    assert(ordered_pockets_by_price_with_given_destination(test_list, date(2021, 11, 3), date(2021, 11, 10)) == [[date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 1200], [date(2021, 11, 3), date(2021, 11, 10), 'Tenerife', 2400]])
    assert (ordered_pockets_by_price_with_given_destination(test_list, date(2024, 11, 3), date(2024, 11, 10)) == [])
    print("test_ordered_pockets_by_price_with_given_destination passed")

test_create_pocket()
test_add_pocket_to_list()
test_valid_period()
test_remove_pocket_with_destination()
test_remove_pocket_with_smaller_duration()
test_fits_in_the_period()
test_nr_pockets_with_given_destination()
test_average_price_of_pockets_with_given_destination()
test_ordered_pockets_by_price_with_given_destination()
start()