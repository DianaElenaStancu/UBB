from datetime import date
from app.domain.travel_packages import generate_pockets, get_start_date, get_finish_date, get_destination, get_price
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

def remove_pocket_with_greater_price_and_different_destination(lst, price, destination):
    """
    Functia creeaza o noua lista cu ofertele care au un preț mai mic decât cel dat sau
    aceeasi destinatie  de cea citită de la tastatură.
    :param lst: lista de pachete de calatorie
    :param price:  pretul calatoriei
    :param destination: destinatia calatoriei
    :return new_list: noua lista
    """
    new_list = []
    for pocket in lst:
        if get_price(pocket) <= price or get_destination(pocket) == destination:
            new_list.append(pocket)
    return new_list

def remove_pocket_with_same_month(lst, month):
    """
    Functia creeaza o noua lista de pachete de calatorie care are ofertele cu sejurul intr-o luna data eliminate
    :param lst: lista de pachete de calatorie
    :param month: luna data de utilizator
    :return new_list: noua lista
    """
    new_list = []
    for pocket in lst:
        if get_start_date(pocket).month != month and get_finish_date(pocket).month != month:
            new_list.append(pocket)
    return new_list


