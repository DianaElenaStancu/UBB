from datetime import date

def create_pocket(start_date, finish_date, destination, price):
    """
    Creeaza un pachet de calatorie cu atributele date
    :param start_date: data de inceput a calatoriei
    :type start_date: date
    :param finish_date: data la care se incheie calatoria
    :type finish_date: date
    :param destination: destinatia calatoriei
    :type destination: string
    :param price: priceul calatoriei
    :type price: int
    :return: pachetul de calatorie
    :rtype: list (len(lst) = 4, lst[0] = start_date, lst[1] = finish_date, lst[2] = destination, lst[3] = price)
    """
    return { "start_date": start_date, "finish_date": finish_date, "destination": destination, "price": price}

def get_start_date(pocket):
    return pocket['start_date']

def get_finish_date(pocket):
    return pocket['finish_date']

def get_destination(pocket):
    return pocket['destination']

def get_price(pocket):
    return pocket['price']

def set_start_date(pocket, start_date):
    pocket['start_date'] = start_date

def set_finish_date(pocket, finish_date):
    pocket['finish_date'] = finish_date

def set_destination(pocket, destination):
    pocket['destination'] = destination

def set_price(pocket, price):
    pocket['price'] = price



