from datetime import date
def generate_pockets():
    return [
        {"start_date": date(2021, 11, 3), "finish_date": date(2021, 11, 10), "destination": 'Tenerife', "price": 1200},
        {"start_date": date(2021, 11, 20), "finish_date": date(2021, 11, 30), "destination": 'Paris', "price": 1500},
        {"start_date": date(2022, 8, 10), "finish_date": date(2022, 8, 17), "destination": 'Dubai', "price": 1600},
        {"start_date": date(2022, 3, 3), "finish_date": date(2022, 3, 8), "destination": 'Paris', "price": 900},
        {"start_date": date(2022, 1, 1), "finish_date": date(2022, 2, 1), "destination": 'Constanta', "price": 1000},
        {"start_date": date(2022, 4, 8), "finish_date": date(2022, 4, 11), "destination": 'Viena', "price": 500}]

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



