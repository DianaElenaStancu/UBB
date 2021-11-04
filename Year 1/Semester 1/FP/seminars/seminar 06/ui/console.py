from termcolor import colored

class Console:
    def __init__(self, srv):
        self.__srv = srv

    # def __show_all_products(self):
    #     products = self.__serv.__repo.get_all_products()
    # nu este corect dpdv al arhitecturii



    def __show_all_products(self):
        products = self.__srv.get_all_products()
        if len(products) == 0:
            print(colored("Nu exista produse in lista", 'magenta'))
        else:
            print('Lista de produse este: ')
            for product in products:
                # print(product)
                print('-Denumire: ', colored(product.getName(), 'cyan'), ' -Stoc:', colored(product.getStoc(), 'cyan'),
                      ' -Pret:', colored(product.getPret(), 'cyan'))

    def __add_product(self):  # doar local folosita, __
        denumire = input('Denumirea produsului: ')
        try:
            stoc = int(input('Nr. de unitati in stoc: '))
            pret = float(input('Pretul produsului: '))
        except ValueError:
            print(colored('Stoc/pret trebuie sa fie numere.', 'red'))

        try:
            added_product = self.__srv.add_product(denumire, stoc, pret)
            print('Produsul', added_product, 'a fost adaugat cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    def show_ui(self):  # metoda publica folosita in afara clasei
        while True:
            print("Comenzi disponibile: add, delete, show_all, undo, exit")
            cmd = input("Comanda este: ")
            cmd = cmd.lower().strip()  # converteste in litere mici si eliminta spatiile in plus
            if cmd == 'add':
                self.__add_product()
            elif cmd == 'show_all':
                self.__show_all_products()
            elif cmd == 'exit':
                return
            else:
                print(colored('Comanda invalida', 'red'))
