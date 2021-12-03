from termcolor import colored
from validator.validator import valideaza_numar, valideaza_baza, valideaza_cifra, valideaza_convertire_rapida
from domain.calculator import sum, dif, mul, div
from domain.conversions import convert_rapid, convert_directa, convert_intermediar


def printeaza_Meniu():
    """
    Printeaza meniul principal
    """
    print(colored("----------", 'blue'))
    print(colored("Calculator menu", 'blue'))
    print(colored("Bazele ce pot fi introduse sunt de la 2->16", 'blue'))
    print(colored("+ -> suma a doua numere intr-o baza oarecare", 'blue'))
    print(colored("- -> diferenta a doua numere intr-o baza oarecare", 'blue'))
    print(colored("* -> inmultirea unui numar cu o cifra intr-o baza oarecare", 'blue'))
    print(colored("/ -> impartirea unui numar cu o cifra intr-o baza oarecare", 'blue'))
    print(colored("cr -> converteste dintr-o baza putere a lui 2 in alta baza putere a lui 2", 'blue'))
    print(colored("ci -> converteste dintr-o baza in alta baza folosind o baza intermediara (10)", 'blue'))
    print(colored("cd -> converteste direct dintr-o baza in alta baza", 'blue'))
    print(colored("x -> iesire din aplicatie", 'blue'))

def sum_ui():
    """
    Citeste de la tastatura:
      baza - baza in care se va face suma celor doua numere,
      tip baza: int (2->16)
      a - primul numar
      b - al doilea numar
      tip a, b: str
    Se valideaza datele citite de la tastatura:
        In cazul in care baza nu apartine [2,16] sau in cazul in care numarul a, respectiv b nu apartin bazei baza
        se va afisa o un mesaj de eroare
    Afiseaza suma celor doua numere:
        raspuns - variabila de tip str
    """
    try:
        baza = int(input("Baza in care doriti sa adunati numerele: "))
        a = input("Primul numar: ").upper()
        b = input("Al doilea numar: ").upper()
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
    Citeste de la tastatura:
      baza - baza in care se va face diferenta celor doua numere,
      tip baza: int (2->16)
      a - primul numar
      b - al doilea numar
      tip a, b: str
    Se valideaza datele citite de la tastatura:
        In cazul in care baza nu apartine [2,16] sau in cazul in care numarul a, respectiv b nu apartin bazei baza
        se va afisa o un mesaj de eroare
    Afiseaza diferenta celor doua numere:
        raspuns - variabila de tip str
    """
    try:
        baza = int(input("Baza in care doriti sa scadeti numerele: "))
        a = input("Primul numar: ").upper()
        b = input("Al doilea numar: ").upper()
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
    Citeste de la tastatura:
      baza - baza in care se va face inmultirea celor doua numere,
      tip baza: int (2->16)
      a - numar
      c - cifra
      tip a, c: str
    Se valideaza datele citite de la tastatura:
        In cazul in care baza nu apartine [2,16] sau in cazul in care numarul a, respectiv c nu apartin bazei baza
        se va afisa un mesaj de eroare
    Afiseaza inmultirii celor doua numere:
        raspuns - variabila de tip str
    """
    try:
        baza = int(input("Baza in care doriti sa inmultiti numerele: "))
        a = input("Primul numar: ").upper()
        c = input("Al doilea numar (cifra): ").upper()
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
    Citeste de la tastatura:
      baza - baza in care se va face impartirea celor doua numere,
      tip baza: int (2->16)
      a - numar
      c - cifra
      tip a, c: str
    Se valideaza datele citite de la tastatura:
        In cazul in care baza nu apartine [2,16] sau in cazul in care numarul a, respectiv c nu apartin bazei baza
        se va afisa un mesaj de eroare
    Afiseaza impartirea celor doua numere:
        raspuns - variabila de tip str
    """
    try:
        baza = int(input("Baza in care doriti sa impartiti numerele: "))
        a = input("Primul numar: ").upper()
        c = input("Al doilea numar (cifra): ").upper()
        valideaza_baza(baza)
        valideaza_numar(a, baza)
        valideaza_cifra(c, baza)
        impartire = div(a, c, baza)
        cat = impartire[0]
        rest = impartire[1]
        raspuns = "Raspunsul este: " + a + "(" + str(baza) + ")" + "/" + c + "(" + str( baza) + ")" + "=" + cat + "(" + str(baza) + ")" + "rest" + rest + "(" + str(baza) + ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def convert_rapid_ui():
    """
    Citeste de la tastatura:
      baza_sursa: baza din care se doreste conversia rapida
      baza_destinatie: baza in care se doreste conversia rapida
      tip baza_sursa, baza_destinatie: int
      a: numarul care se doreste a fi convertit
      tip a: str
    Se valideaza datele citite de la tastatura:
        In cazul in care bazele nu apartin multimii {2,4,8,16} sau in cazul in care numarul a nu apartine bazei baza_sursa
        se va afisa un mesaj de eroare
    Afiseaza numarul convertit:
        raspuns - variabila de tip str
    """
    try:
        baza_sursa = int(input("Baza sursa (2,4,8,16):"))
        baza_destinatie = int(input("Baza destinatie (2,4,8,16):"))
        a = input("Numarul pe care vrei sa il convertesti: ").upper()
        valideaza_numar(a, baza_sursa)
        valideaza_convertire_rapida(baza_sursa, baza_destinatie)
        numar = convert_rapid(a, baza_sursa, baza_destinatie)
        raspuns = "Raspunsul este: " + numar + "(" + str(baza_destinatie) + ")"
        print(colored(raspuns, 'blue'))
    except ValueError as ve:
        print(colored(str(ve), 'red'))

def convert_intermediar_ui():
    """
    Citeste de la tastatura:
      baza_sursa: baza din care se doreste conversia cu o baza intermediara
      baza_destinatie: baza in care se doreste conversia cu o baza intermediara
      tip baza_sursa, baza_destinatie: int
      a: numarul care se doreste a fi convertit
      tip a: str
    Se valideaza datele citite de la tastatura:
        In cazul in care bazele nu apartin intervalului [2,16] sau in cazul in care numarul a nu apartine bazei baza_sursa
        se va afisa un mesaj de eroare
    Afiseaza numarul convertit:
        raspuns - variabila de tip str
    """
    try:
        baza_sursa = int(input("Baza sursa:"))
        baza_destinatie = int(input("Baza destinatie:"))
        a = input("Numarul pe care vrei sa il convertesti: ").upper()
        valideaza_numar(a, baza_sursa)
        valideaza_baza(baza_sursa)
        valideaza_baza(baza_destinatie)
        numar = convert_intermediar(a, baza_sursa, baza_destinatie)
        raspuns = "Raspunsul este: " + numar + "(" + str(baza_destinatie) + ")"
        print(colored(raspuns, 'blue'))

    except ValueError as ve:
        print(colored(str(ve), 'red'))



def convert_direct_ui():
    """
    Citeste de la tastatura:
      baza_sursa: baza din care se doreste conversia directa
      baza_destinatie: baza in care se doreste conversia directa
      tip baza_sursa, baza_destinatie: int
      a: numarul care se doreste a fi convertit
      tip a: str
    Se valideaza datele citite de la tastatura:
        In cazul in care bazele nu apartin intervalului [2,16] sau in cazul in care numarul a nu apartine bazei baza_sursa
        se va afisa un mesaj de eroare
    Afiseaza numarul convertit:
        raspuns - variabila de tip str
    """
    try:
        baza_sursa = int(input("Baza sursa:"))
        baza_destinatie = int(input("Baza destinatie:"))
        a = input("Numarul pe care vrei sa il convertesti: ").upper()
        valideaza_numar(a, baza_sursa)
        valideaza_baza(baza_sursa)
        valideaza_baza(baza_destinatie)

        numar = convert_directa(a, baza_sursa, baza_destinatie)

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
        elif(cmd == "ci"):
            convert_intermediar_ui()
        elif(cmd == "cd"):
            convert_direct_ui()
        else:
            print(colored("Comanda invalida", 'red'))
    print(colored("Bye", 'blue'))