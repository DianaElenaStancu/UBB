from termcolor import colored
from domain.calculator import sum
def printeaza_Meniu():
    """
    Printeaza meniul principal
    """
    print(colored("----------", 'blue'))
    print(colored("Calculator menu", 'blue'))
    print(colored("+ -> suma a doua numere intr-o baza oarecare", 'blue'))
    print(colored("- -> diferenta a doua numere intr-o baza oarecare", 'blue'))
    print(colored("* -> inmultirea unui numar cu o cifra baza oarecare", 'blue'))
    print(colored("/ -> impartirea unui numar cu o cifra baza oarecare", 'blue'))
    print(colored("exit", 'blue'))

def sum_ui():
    """
    Citeste de la tastatura:
      baza - baza in care se va face suma celor doua numere
      a - primul numar
      b - al doilea numar
    """
    baza = int(input("Baza in care doriti sa adunati numerele: "))
    a = input("Primul numar: ")
    b = input("Al doilea numar: ")
    try:
        suma = sum(a, b, baza)
        print(suma)
    except:
        print(colored("Eroare!", 'red'))

def run():
    """
    implementarea interfetei cu utilizatorul
    """
    exit = False
    while not exit:
        printeaza_Meniu()
        cmd = input("Comanda ta este:").strip()
        if(cmd == 'exit'):
            exit = True
        elif(cmd == '+'):
            sum_ui()
        else:
            print(colored("Comanda invalida", 'red'))
    print(colored("Bye", 'blue'))