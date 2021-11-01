"""
P6. AGENȚIE DE TURISM
Creați o aplicație pentru gestiunea pachetelor de călătorie oferite de o agenție de
turism. Aplicația stochează pachete de călătorie oferite clienților după cum
urmează: data de început și cea de sfârșit a călătoriei, destinația și prețul.

Aplicația va permite:
    1. Adăugare
        • Adaugă pachet de călătorie
        • Modifică pachet de călătorie
    2. Ștergere
        • Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată
        • Ștergerea tuturor pachetelor de călătorie care au o durată mai scurtă decât un număr de zile dat
        • Ștergerea tuturor pachetelor de călătorie care au prețul mai mare decât o sumă dată
    3. Căutare
        • Tipărirea pachetelor de călătorie care presupun un sejur într-un interval dat (e.g. 10/08/2018 - 24/08/2018 -
        un pachet valid este cel a cărui dată de început este aceeași sau după de data de început citită și data de
         sfârșit este înainte sau aceeași cu data de sfârșit introdusă de la tastatură)
        • Tipărirea pachetelor de călătorie cu o destinație dată și cu preț mai mic decât o sumă dată.
        • Tipărirea pachetelor de călătorie cu o anumită dată de sfârșit
    4. Rapoarte
        • Tipărirea numărului de oferte pentru o destinație dată.
        • Tipărirea tuturor pachetelor disponibile într-o anumită perioadă citită de la tastatură (vezi 3.i.) în
        ordinea crescătoare a prețului.
        • Tipărirea mediei de preț pentru o destinație dată
    5. Filtrare
        • Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la
        tastatură
        • Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună (citită de la tastatură sub forma
        unui număr natural între 1 și 12)
    6. Undo
        • Refacerea ultimei operații (lista de oferte revine la ce exista înainte de ultima operație care a modificat
        lista) – Nu folosiți funcția deepCopy
"""

from ui.console import start

start()

""""""
#start()