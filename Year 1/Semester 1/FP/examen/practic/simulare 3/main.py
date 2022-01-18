"""
creati o aplicatie pentru gestiunea produselor intr-un magazin.
la pornire aplicatia incarca toate produsele dintr-un fisier text.
aplicatia permite:
    1. adaugare de produse. se da id, denumire, pret, alicatia salveaza imediat produsul in fisier

    2. sterge produse. se da o cifra se sterg toate produsele pentru care pretul produslui contine
    o cifra data, afiseaza un mesaj cu numarul produselor sterse (modificarile se vad imediat in fisier)

    3. filtrare produse. utilizatorul poate seta un filtru constand intr-un text si un numar (sirul vid daca nu mai
    doreste filtrarea dupa denumire si -1 daca nu vrea filtru curent).
    aplicatia afiseaza filtru curent si lista produselor (aplicand filtrul curent) dupa actionarea oricarui element de meniu
    sunt incluse produsele care in denumire contin textul si au pretul mai mic decat pretul din filtru
    filtrarea nu afecteaza fisierul cu produse

    4. undo ultima operatie de stergere. aplicatia reface ultima operatie de stergere, aplicatia reface ...
"""
from domain.validator import Validator
from repository.repository import Repository
from service.service import Service
from testing.tests import Testing
from ui.console import Console

tests = Testing()
tests.run()

repo = Repository("repository/produse.txt")
val = Validator()
srv = Service(repo, val)
console = Console(srv)
console.run()
