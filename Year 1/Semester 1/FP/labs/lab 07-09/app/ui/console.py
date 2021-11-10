from termcolor import colored
from app.repository.events_repo import RepositoryException

class Console:
    def __init__(self, PersonSrv, EventSrv):
        self.__person_srv = PersonSrv
        self.__event_srv = EventSrv

    #event
    def __show_all_events(self):
        """
        afiseaza toate evenimentele disponibile
        """
        events = self.__event_srv.get_all_events()
        if len(events) == 0:
            print(colored('Nu exista evenimente in lista', 'yellow'))
        else:
            print(colored('Lista de evenimente este:', 'yellow'))
            for event in events:
                print(colored(event, 'yellow'))

    def __add_event(self):
        """
        adauga eveniment
        """
        date = input("Data in formatul YYYY-MM-DD: ")
        time = input("Ora in formatul HH:MM: ")
        description = input("Descrierea: ")
        try:
            added_event = self.__event_srv.add_event(date, time, description)
            print("Eveniment: ", colored(added_event, 'yellow'), 'a fost adaugata cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    def __del_event(self):
        """
        sterge eveniment
        """
        try:
            id = int(input("Id-ul evenimentului pe care vrei sa il stergi: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        try:
            deleted_event = self.__event_srv.delete_event(id)
            print("Evenimentul: ", colored(deleted_event, 'yellow'), 'a fost stearsa cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))
        except RepositoryException as ve:
            print(colored(str(ve), 'orange'))

    def __mod_event(self, field):
        """modifica eveniment"""
        try:
            id = int(input("Id-ul evenimentului pe care vrei sa o modifici: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        if field == 'date':
            value = input("Data in formatul YYYY-MM-DD: ")
        elif field == 'time':
            value = input("Ora in formatul HH:MM: ")
        else:
            value = input("Descrierea: ")

        try:
            modified_event = self.__event_srv.modify_event(id, field, value)
            print("Evenimentul: ", colored(modified_event, 'yellow'), 'a fost modificat cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    #person
    def __show_all_persons(self):
        """
        afiseaza toate produsele disponibile
        """
        persons = self.__person_srv.get_all_persons()
        if len(persons) == 0:
            print(colored('Nu exista persoane in lista', 'yellow'))
        else:
            print(colored('Lista de persoane este:', 'yellow'))
            for person in persons:
                print(colored(person, 'yellow'))

    def __add_person(self):
        """
        adauga produs
        """
        name = input("Numele persoanei: ")
        address = input("Adresa persoanei: ")
        try:
            added_person = self.__person_srv.add_person(name, address)
            print("Persoana: ", colored(added_person, 'yellow'), 'a fost adaugata cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    def __del_person(self):
        """
        sterge persoana
        """
        try:
            id = int(input("Id-ul persoanei pe care vrei sa o stergi: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        try:
            deleted_person = self.__person_srv.delete_person(id)
            print("Persoana: ", colored(deleted_person, 'yellow'), 'a fost stearsa cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))

    def __mod_person(self, field):
        """modifica persoana"""
        try:
            id = int(input("Id-ul persoanei pe care vrei sa o modifici: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        if field == 'name':
            value = input("Numele nou al persoanei: ")
        else:
            value = input("Adresa noua a persoanei: ")
        try:
            modified_person = self.__person_srv.modify_person(id, field, value)
            print("Persoana: ", colored(modified_person, 'yellow'), 'a fost modificata cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))



    def show_ui(self):
        exit = False
        while not exit:
            print('Comenzi disponibile pentru persoane: add_person, del_person, mod_person_[name/address], show_persons')
            print('Comenzi disponibile pentru evenimente: add_event, del_event, mod_event_[date/time/description], show_events')
            print('Alte comenzi: exit')
            cmd = input('Comanda este: ')
            cmd = cmd.lower().strip()
            if cmd == 'add_person':
                self.__add_person()
            elif cmd == 'del_person':
                self.__del_person()
            elif cmd.find('mod_person_') != -1 and (cmd[11:] == 'name' or cmd[11:] == 'address'):
                field = cmd[11:]
                self.__mod_person(field)
            elif cmd == 'show_persons':
                self.__show_all_persons()
            elif cmd == 'add_event':
                self.__add_event()
            elif cmd == 'del_event':
                self.__del_event()
            elif cmd.find('mod_event_') != -1 and (cmd[10:] == 'date' or cmd[10:] == 'time' or cmd[10:] == 'description'):
                field = cmd[10:]
                self.__mod_event(field)
            elif cmd == 'show_events':
                self.__show_all_events()
            elif cmd == 'exit':
                exit = 1
            else:
                print(colored('Comanda invalida', 'red'))
        return
