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
                print('ID: ', colored(product.getId(), 'cyan'), ' -Denumire: ', colored(product.getName(), 'cyan'), ' -Stoc:', colored(product.getStoc(), 'cyan'),
                      ' -Pret:', colored(product.getPret(), 'cyan'))

    def __add_product(self):  # doar local folosita, __
        id = input('Id-ul produsului: ')
        denumire = input('Denumirea produsului: ')
        try:
            stoc = int(input('Nr. de unitati in stoc: '))
            pret = float(input('Pretul produsului: '))
        except ValueError:
            print(colored('Stoc/pret trebuie sa fie numere.', 'red'))

        try:
            added_product = self.__srv.add_product(id, denumire, stoc, pret)
            print('Produsul', added_product, 'a fost adaugat cu succes.')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    def delete_product(self):
        id = input('Id produs: ')
        try:
            deleted_product = self.__srv.delete_by_id(id)
            print('Produsul', deleted_product, 'a fost sters cu succes')
        except ValueError as ve:
            print(colored(str(ve), 'red'))

    def show_ui(self):  # metoda publica folosita in afara clasei
        while True:
            print("Comenzi disponibile: add, delete_by_id, show_all, undo, exit")
            cmd = input("Comanda este: ")
            cmd = cmd.lower().strip()  # converteste in litere mici si eliminta spatiile in plus
            if cmd == 'add':
                self.__add_product()
            elif cmd == 'show_all':
                self.__show_all_products()
            elif cmd == 'delete_by_id':
                self.__delete_product()
            elif cmd == 'exit':
                return
            else:
                print(colored('Comanda invalida', 'red'))
