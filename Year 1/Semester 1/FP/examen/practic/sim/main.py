import string
import random
from random import randint

from domain.validator import Validator
from repository.repository import Repository
from service.service import Service
from ui.console import Console

repo = Repository("repository/piese.txt")
val = Validator()
srv = Service(repo, val)
console = Console(srv)
#console.run()

def random_string(ln=None):
    """genereaza un string random"""
    ln = ln if ln is not None else randint(1,20)
    pos = randint(2, ln-3)
    lit = string.ascii_letters
    voc = "aeiouAEIOU"
    str_list = [random.choice([random.choice(lit), random.choice(voc)])for _ in range(ln)]
    str_list[pos] = ' '
    random_str = "".join(str_list)

    return random_str

print(random_string())
