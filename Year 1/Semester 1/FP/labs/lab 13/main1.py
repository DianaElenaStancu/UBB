"""
pentru lista de monede cu valorile a1, ..., an si o valoare S.
tipariti toate modalitatile de a plati suma S cu monedele disponibile.
Tipariti un mesaj daca suma nu se poate plati
"""
from functools import reduce

"""
descriere solutie bkt
monede = lista de monede, lungimea liste = len(monede)
solutia candidat:
x = (x0, x1, x2, ..., xk), k < len(monede)
xi e monede, orice i = 0,k

conditie consistenta:
x0 + x1 + x2 + ... + xk  < S
occ(xi, x) <= occ(xi, monede)
numarul de aparitii a lui xi in lista x sa fie mai mic 
sau egal decat numarul de aparitii a lui xi in lista de
monede

conditie solutie:
x - consistenta si  x0 + x1 + x2 + ... + xk = S
"""
solutions = []
def consistent(x, l, s):
    suma = reduce(lambda x, y: x + y, x)
    if suma > s:
        return False
    copyL = l[:]
    for i in range(1, len(x)):
        if x[i-1] > x[i]:
            return False
    for el in x:
        if el in copyL:
            copyL.remove(el)
        else:
            return False
    return True

def solutie(x, s):
    suma = reduce(lambda x, y: x + y, x)
    return suma == s and x not in solutions

def backRec(x, l, s):
    x.append(0)
    for i in range(len(l)):
        x[-1] = l[i]
        if consistent(x, l, s):
            if solutie(x, s):
                solutions.append(x[:])
                print(x)
            else:
                backRec(x, l,s)
    x.pop()



monede = [1, 1, 1, 2, 2, 3, 5, 10, 20, 50]
#sortam lista
monede = sorted(monede)
s = 6
backRec([], monede, s)
if len(solutions) == 0:
    print("n-ai bani :(")