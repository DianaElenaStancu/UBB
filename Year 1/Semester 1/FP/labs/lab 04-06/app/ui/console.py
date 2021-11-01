from termcolor import colored
from datetime import date
from domain.travel_packages import *
from utils.list_operations import *

#UI FUNCTIONS
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
    print(colored('Filtrare', 'magenta'))
    print('12. Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură.')
    print('13. Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună.')
    print(colored('Undo', 'magenta'))
    print('14. Refacerea ultimei operații.')
    print(colored('Alte functionalitati', 'magenta'))
    print('P Afișează lista de pachete de călătorie')
    print('X Închide aplicația')
    print(colored('**********************************\n', 'yellow'))

def print_pocket(nr, lst):
    pocket = lst[nr]
    print("Nr pachet: ", nr+1, "| Data de inceput:", get_start_date(pocket), "| Data de sfarsit:", get_finish_date(
        pocket), "| Destinatie:", get_destination(pocket), "| Pret:", get_price(pocket))

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
    destination = input(colored("Destinatia calatoriei: ", 'yellow'))
    if destination == '':
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

def read_month():
    """
    Citeste o luna din an
    :return:
    """
    try:
        month = int(input(colored("Luna din an: ", 'yellow')))
        if month < 1 or month > 12:
            exception()
            return read_month()
    except ValueError:
        exception()
        return read_duration()
    return month

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
    pocket = create_pocket(start_date, finish_date, destination, price)
    add_pocket_to_list(lst, pocket)
    print(colored('Adaugarea pachetului a fost efectuata cu succes', 'yellow'))

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
    pocket = lst[pocket_number]
    pocket_number -= 1
    print("Pachetul pe care il vei modifica este: ")
    print_pocket(pocket_number,lst)
    finished = False
    while not finished:
        print_change_pocket_menu()
        option = input(colored("Optiunea este: ", 'yellow'))
        if option.lower() == 's':
            start_date = read_date()
            set_start_date(pocket, start_date)
        elif option.lower() == 'f':
            finish_date = read_date()
            set_finish_date(pocket, finish_date)
        elif option.lower() == 'd':
            destination = read_destination()
            set_destination(pocket, destination)
        elif option.lower() == 'p':
            price = read_price()
            set_price(pocket, price)
        elif option.lower() == 'x':
            finished = True
        else:
            exception()
        if not valid_period(get_start_date(lst[pocket_number]), get_finish_date(lst[pocket_number])):
            print(colored("Trebuie sa modifici intervalul calatoriei pentru ca nu este valid", 'red'))
            finished = False
    print(colored('Modificarea pachetului a fost efectuata cu succes', 'yellow'))

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
    while not valid_period(start_date, finish_date):
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
    if len(new_list) == 0:
        print("Nu exista pachete :(")
    else:
        for pocket_number in range(0, len(new_list)):
            print_pocket(pocket_number, new_list)

def remove_pocket_with_greater_price_and_different_destination_ui(lst):
    """
    Functia citeste pretul si destinatia oferita de utilizator si returneaza lista cu ofertele
    care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură eliminate.
    :param lst: lista de oferte
    :return new_list: lista de oferte modificata
    """
    price = read_price()
    destination = read_destination()
    new_list = remove_pocket_with_greater_price_and_different_destination(lst, price, destination)
    return new_list

def remove_pocket_with_same_month_ui(lst):
    """
    Functia citeste luna si afiseaza lista de pachete care au ofertele cu sejurul in luna data eliminate
    :param lst: lista de pachete
    :return new_list: lista modificata
    """
    month = read_month()
    new_list = remove_pocket_with_same_month(lst, month)
    return new_list

def start():
    crt_pocket_list = generate_pockets()
    finished = False
    while not finished:
        print_menu()
        option = input(colored('Optiunea este: ', 'yellow'))
        if option == '1':
            add_pocket_ui(crt_pocket_list)
        elif option == '2':
            change_pocket_ui(crt_pocket_list)
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
        elif option == '12':
            crt_pocket_list = remove_pocket_with_greater_price_and_different_destination_ui(crt_pocket_list)
            print(colored(
                'Eliminarea a fost efectuata cu succes',
                'yellow'))
        elif option == '13':
            crt_pocket_list = remove_pocket_with_same_month_ui(crt_pocket_list)
            print(colored(
                'Eliminarea a fost efectuata cu succes',
                'yellow'))
        elif option.lower() == 'p':
            print_pocket_list(crt_pocket_list)
        elif option.lower() == 'x':
            print(colored('Bye bye!', 'magenta'))
            finished = True
        else:
            exception()
