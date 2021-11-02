from datetime import date

def generate_pockets():
    return [
        {"start_date": date(2021, 11, 3), "finish_date": date(2021, 11, 10), "destination": 'Tenerife', "price": 1200},
        {"start_date": date(2021, 11, 20), "finish_date": date(2021, 11, 30), "destination": 'Paris', "price": 1500},
        {"start_date": date(2022, 8, 10), "finish_date": date(2022, 8, 17), "destination": 'Dubai', "price": 1600},
        {"start_date": date(2022, 3, 3), "finish_date": date(2022, 3, 8), "destination": 'Paris', "price": 900},
        {"start_date": date(2022, 1, 1), "finish_date": date(2022, 2, 1), "destination": 'Constanta', "price": 1000},
        {"start_date": date(2022, 4, 8), "finish_date": date(2022, 4, 11), "destination": 'Viena', "price": 500}]

def setup_history(add_predefined):
    """
    Initializeaza un obiect de tip magazin
   :param add_predefined: indicator pentru adaugarea pachetelor predefinite (daca True
            lista initiala este cea care contine pachetele predefinite, altfel, lista initiala de produse este goala)
    :type add_predefined: bool
    :return: lista in care primul element reprezinta lista curenta de produse, si al doilea element lista pentru undo
    :rtype: list
    """
    store = []
    store.append([])
    if add_predefined:
        pocket_list = generate_pockets()
        store.append(pocket_list)
    return store

def get_pocket_list(history):
    return history[-1]

def add_new_list_to_history(history, lst):
    history.append(lst)

def undo(history):
    """
    Face undo la ultima operatie de adaugare sau stergere
    :param history:
    :type history: list (len(list)=2, list[0] - lista curenta de produse, list[1] - lista de undo
    :return: lista curenta se modifica prin revenire la starea listei inainte de operatie
    :rtype: -;
    :raises: ValueError daca nu se mai poate face undo
    """
    # crt_product_list = get_pocket_list(history)
    if len(history) == 1:
        raise ValueError("Nu se mai poate face undo.")
    else:
        history.pop()
