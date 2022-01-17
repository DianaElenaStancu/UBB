"""
creati o aplicatie pentru gestiunea cartilor intr-o biblioteca.
la pornire aplicatia incarca toate cartile dintr-un fisier text.
aplicatie permite:
    1. adaugare de carte. se da: id, titlu, autor, anAparitie, aplicatia salveaza
    imediat cartea in fisier
    2. modifica carti. se da o cifra si un autor se modifica autorul pentru toate
    cartile pnetru care id contine cifra data (modifica se vad imediat in fisier)
    3. undo multiplu. aplicatia reface ultima operatie(adauga, modifica). se poate
    da undo de mai multe ori (la mai multe operatii executate inainte).
    modificarea se reflecta si in fisier
    4. filtrare carti dupa titlu si anAparitie. la pornirea aplicatia filtru este
    setat pe sir vid si -1 (se vad toate cartile din fisier). Utilizatorul poate
    modifica filtru oricand, folosind o comanda din meniul aplicatiei (da un alt text si
    alt numar). aplicatia afiseaza filtru curent si lista cartilor (aplicand filtru curent)
    la pornire si dupa actionarea oricarui element de meniu. la afisare sunt incluse produsele
    care in titlu contin textul si au anul mai mic decat anul din filtru.
    filtrarea nu afecteaza fisierul cu cartile
"""
from domain.validators import Validator
from repository.repository import Repository
from service.service import Service
from testing.tests import Test
from ui.console import Console

test = Test()
test.runAll()
print("tests passed :)")
validator = Validator()
repository = Repository("repository/carti.txt")
service = Service(repository, validator)
console = Console(service)
console.run()