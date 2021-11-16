from termcolor import colored
from app.repository.events_repo import RepositoryException

class PersonUI:
    def __init__(self, PersonSrv):
        self.__person_srv = PersonSrv
        self.__comands = {
            "generate": self.__generate_persons,
            "add":self.__add_person,
            "del":self.__del_person,
            "mod":self.__mod_person,
            "find":self.__find_person,
            "show":self.__show_all_persons
        }

    def run(self):
        back = False
        while not back:
            print(colored('-------------------', 'blue'))
            print(colored('Comenzile disponibile: generate/add/del/mod/find/show/back', 'blue'))
            print(colored('-------------------', 'blue'))
            cmd = input("Comanda este: ")
            cmd = cmd.lower().strip()
            if cmd in self.__comands:
                self.__comands[cmd]()
            elif cmd == "back":
                back = True
            else:
                print(colored("Comanda invalida", 'red'))

    def __generate_persons(self):
        """
        genereaza un numar de persoane introdus de utilizator
        """
        try:
            nr = int(input("Numarul de persoane pe care vrei sa le generezi: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        self.__person_srv.generate_persons(nr)

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
            return


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
            return
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

    def __mod_person(self):
        """modifica persoana"""
        try:
            id = int(input("Id-ul persoanei pe care vrei sa o modifici: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        field = input("Campul pe care vrei sa il modifici (name/address): ")
        if field != "name" and field != "address":
            print(colored("Field inexistent", 'red'))
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
            return
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

    def __find_person(self):
        """cauta persoana dupa un field dat"""

        field = input("Campul pe care vrei sa cauti(id/name/address): ")

        if field != "name" and field != "address" and field != "id":
            print(colored("Field inexistent", 'red'))
            return

        if field == "id":
            try:
                value = int(input("Id-ul persoanei dupa care vrei sa cauti: "))
            except ValueError as ve:
                print(colored(str(ve), 'red'))
                return
        elif field == "name":
            value = input("Numele persoanei dupa care vrei sa cauti: ")
        else:
            value = input("Adresa persoanei dupa care vrei sa cauti: ")

        try:
            searched_persons = self.__person_srv.search_person(field, value)
            print("Persoanele/Persoana cautate/cautat sunt/este:")
            for person in searched_persons:
                print(colored(person, 'yellow'))
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

class EventUI:
    def __init__(self, EventSrv):
        self.__event_srv = EventSrv
        self.__comands = {
            "generate": self.__generate_event,
            "add": self.__add_event,
            "del": self.__del_event,
            "mod": self.__mod_event,
            "find": self.__find_event,
            "show": self.__show_all_events
        }

    def run(self):
        back = False
        while not back:
            print(colored('-------------------', 'blue'))
            print(colored('Comenzile disponibile: generate/add/del/mod/find/show/back', 'blue'))
            print(colored('-------------------', 'blue'))
            cmd = input("Comanda este: ")
            cmd = cmd.lower().strip()
            if cmd in self.__comands:
                self.__comands[cmd]()
            elif cmd == "back":
                back = True
            else:
                print(colored("Comanda invalida", 'red'))

    def __generate_event(self):
        """genereaza un numar de evenimente"""
        try:
            nr = int(input("Numarul de evenimente pe care vrei sa le generezi: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        self.__event_srv.generate_events(nr)

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
            return

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
            return
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

    def __mod_event(self):
        """modifica eveniment"""

        try:
            id = int(input("Id-ul evenimentului pe care vrei sa o modifici: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        field = input("Campul pe care vrei sa il modifici (date/time/description): ")
        if field != "date" and field != "time" and field != "description":
            print(colored("Field inexistent", 'red'))
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
            return
        except RepositoryException as re:
            print(colored(str(re), 'magenta'))
            return

    def __find_event(self):
        """cauta evenimentul dupa un field dat"""

        field = input("Campul dupa care vrei sa cauti (id/date/time): ")
        if field != "id" and field != "date" and field != "time":
            print(colored("Field inexistent", 'red'))
            return

        if field == "id":
            try:
                value = int(input("Id-ul dupa care doriti sa cautati: "))
            except ValueError as ve:
                print(colored(str(ve), 'red'))
                return
        elif field == "date":
            value = input("Data in formatul YYYY-MM-DD: ")
        else:
            value = input("Timpul in formatul HH:MM: ")
        try:
            searched_events = self.__event_srv.search_event(field, value)
            print("Evenimentul/evenimentele cautat/cautate este/sunt: ")
            for event in searched_events:
                print(colored(event, 'yellow'))
        except RepositoryException as re:
            print(colored(str(re), 'magenta'))
            return
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

class ParticipationUI:
    def __init__(self, ParticipationSrv):
        self.__participation_srv = ParticipationSrv
        self.__comands = {
            "sign": self.__sign_person_to_event,
            "unsign": self.__unsign_person_to_event,
            "show": self.__show_participations
        }
    def run(self):
        back = False
        while not back:
            print(colored('-------------------', 'blue'))
            print(colored('Comenzile disponibile: sign/unsign/show/back', 'blue'))
            print(colored('-------------------', 'blue'))
            cmd = input("Comanda este: ")
            cmd = cmd.lower().strip()
            if cmd in self.__comands:
                self.__comands[cmd]()
            elif cmd == "back":
                back = True
            else:
                print(colored("Comanda invalida", 'red'))

    def __sign_person_to_event(self):
        """inscriem o persoana la un eveniment"""
        try:
            person_id = int(input("Id-ul persoanei pe care vrei sa o inscrii:"))
            event_id = int(input("Id-ul evenimentul la care vrei sa inscrii persoana: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        try:
            self.__participation_srv.add_participation(person_id, event_id)
            print("Persoana cu id-ul: ", colored(person_id, 'yellow'), 'a fost inscrisa cu succes la evenimentul cu id-ul: ', colored(event_id, 'yellow'))
            #added_participation = self.__participation_srv.add_participation(person_id, event_id)
            #print("Persoana: ", colored(added_participation[0], 'yellow'), 'a fost inscrisa cu succes la evenimentul: ', colored(added_participation[1], 'yellow')) #for Participation v0
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

    def __unsign_person_to_event(self):
        """
        stergem o participare
        """
        try:
            person_id = int(input("Id-ul persoanei pe care vrei sa o stergi:"))
            event_id = int(input("Id-ul evenimentul la care vrei sa stergi persoana: "))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return

        try:
            deleted_participation = self.__participation_srv.del_participation(person_id, event_id)
            #print("Persoana: ", colored(deleted_participation[0], 'yellow'), 'a fost stearga cu succes de la evenimentul: ', colored(deleted_participation[1], 'yellow')) for Participation(v0)
            print("Persoana cu id-ul: ", colored(person_id, 'yellow'),
                  'a fost stearga cu succes de la evenimentul cu id-ul: ', colored(event_id, 'yellow'))
        except ValueError as ve:
            print(colored(str(ve), 'red'))
            return
        except RepositoryException as ve:
            print(colored(str(ve), 'magenta'))
            return

    def __show_participations(self):
        """afisam participarile"""
        participations = self.__participation_srv.get_all_participations()
        if len(participations) == 0:
            print(colored('Nu exista participari in lista', 'yellow'))
        else:
            print(colored('Lista de participari este:', 'yellow'))
            for participation in participations:
                print("Persoana cu id-ul ",colored(participation.getPersonID(), 'yellow'), "este inscrisa la evenimentul cu id-ul", colored(participation.getEventID(), 'yellow'))#for Participation(v1)
                #print("Persoana cu id-ul ", colored(participation.getPerson(), 'yellow'),
                      #"este inscrisa la evenimentul cu id-ul", colored(participation.getEvent(), 'yellow')) #for Participation(v0)

class Console:
    def __init__(self, PersonUI, EventUI, ParticipationUI):
        self.__person_ui = PersonUI
        self.__event_ui = EventUI
        self.__participation_ui = ParticipationUI
        self.__comands = {
            "person" : self.__person_ui.run,
            "event": self.__event_ui.run,
            "participation": self.__participation_ui.run
        }

    def show_ui(self):
        exit = False
        while not exit:
            print("Ruleaza comenzi pentru: person/event/participation ")
            print('Alte comenzi: exit')
            cmd = input("Comanda ta este: ")
            cmd = cmd.lower().strip()
            if cmd in self.__comands:
                self.__comands[cmd]()
            elif cmd == "exit":
                exit = True
            else:
                print(colored("Comanda este invalida", 'red'))


