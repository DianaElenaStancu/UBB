from termcolor import colored
from validator.validator import valideaza_numar, valideaza_baza, valideaza_cifra, valideaza_convertire_rapida
from domain.calculator import sum, dif, mul, div
from domain.conversions import convert_2_to_power_of_2



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
    print(colored("cr -> converteste dintr-o baza in alta baza", 'blue'))
    print(colored("x -> iesire din aplicatie", 'blue'))

def sum_ui():
    """
    Citeste de la tastatura:
      baza - baza in care se va face suma celor doua numere
      a - primul numar
      b - al doilea numar
    """
    try:
        baza = int(input("Baza in care doriti sa adunati numerele: "))
    except ValueError as ve:
        print(colored(str(ve), 'red'))
        return
    a = input("Primul numar: ").upper()
    b = input("Al doilea numar: ").upper()
    try:
        valideaza_baza(baza)
        valideaza_numar(a, baza)
        valideaza_numar(b, baza)
        suma = sum(a, b, baza)
        raspuns = "Raspunsul este: " + a +"("+ str(baza)+ ")"+ "+"+ b+ "("+ str(baza)+ ")"+ "="+ suma+ "("+ str(baza)+  ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def dif_ui():
    """
    citeste de la tastatura
      baza - baza in care se va face diferenta celor doua numere
      a - primul numar
      b - al doilea numar
    """
    try:
        baza = int(input("Baza in care doriti sa adunati numerele: "))
    except ValueError as ve:
        print(colored(str(ve), 'red'))
        return

    a = input("Primul numar: ").upper()
    b = input("Al doilea numar: ").upper()
    try:
        valideaza_baza(baza)
        valideaza_numar(a, baza)
        valideaza_numar(b, baza)
        diferenta = dif(a, b, baza)
        raspuns = "Raspunsul este: " + a +"("+ str(baza)+ ")"+ "-"+ b+ "("+ str(baza)+ ")"+ "="+ diferenta + "("+ str(baza)+  ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def mul_ui():
    """
    citeste de la tastatura
      baza - baza in care se va face inmultirea celor doua numere (numar si cifra)
      a - primul numar
      c - o cifra
    """
    try:
        baza = int(input("Baza in care doriti sa adunati numerele: "))
    except ValueError as ve:
        print(colored(str(ve), 'red'))
        return
    a = input("Primul numar: ").upper()
    c = input("Al doilea numar: ").upper()
    try:
        valideaza_baza(baza)
        valideaza_numar(a, baza)
        valideaza_cifra(c, baza)
        produs = mul(a, c, baza)
        raspuns = "Raspunsul este: " + a + "(" + str(baza) + ")" + "*" + c + "(" + str( baza) + ")" + "=" + produs + "(" + str(baza) + ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def div_ui():
    """
    citeste de la tastatura
      baza - baza in care se va face impartirea celor doua numere (numar si cifra)
      a - primul numar
      c - o cifra
    """
    try:
        baza = int(input("Baza in care doriti sa adunati numerele: "))
    except ValueError as ve:
        print(colored(str(ve), 'red'))
        return
    a = input("Primul numar: ").upper()
    c = input("Al doilea numar: ").upper()
    try:
        valideaza_baza(baza)
        valideaza_numar(a, baza)
        valideaza_cifra(c, baza)
        impartire = div(a, c, baza)
        cat = impartire[0]
        rest = impartire[1]
        raspuns = "Raspunsul este: " + a + "(" + str(baza) + ")" + "*" + c + "(" + str( baza) + ")" + "=" + cat + "(" + str(baza) + ")" + "rest" + rest + "(" + str(baza) + ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def convert_rapid_ui():
    """
    citeste de la tastatura baza sursa, baza destinatie si numarul
    baza trebuie sa fie o putere a lui 2
    """
    try:
        baza_sursa = int(input("Baza sursa (2,4,8,16):"))
        baza_destinatie = int(input("Baza destinatie (2,4,8,16):"))
        a = input("Numarul pe care vrei sa il convertesti: ").upper()
        valideaza_numar(a, baza_sursa)
        valideaza_convertire_rapida(baza_sursa, baza_destinatie)

        if(baza_sursa == 2):
            numar = convert_2_to_power_of_2(a, baza_destinatie)

        raspuns = "Raspunsul este: " + numar + "(" + str(baza_destinatie) + ")"
        print(colored(raspuns, 'blue'))

    except ValueError as ve:
        print(colored(str(ve), 'red'))

def run():
    """
    implementarea interfetei cu utilizatorul
    """
    exit = False
    while not exit:
        printeaza_Meniu()
        cmd = input("Comanda ta este:").strip()
        if(cmd == 'x'):
            exit = True
        elif(cmd == '+'):
            sum_ui()
        elif(cmd == '-'):
            dif_ui()
        elif (cmd == '*'):
            mul_ui()
        elif (cmd == "/"):
            div_ui()
        elif(cmd == "cr"):
            convert_rapid_ui()
        else:
            print(colored("Comanda invalida", 'red'))
    print(colored("Bye", 'blue'))