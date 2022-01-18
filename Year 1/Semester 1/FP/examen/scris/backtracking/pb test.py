"""
Afiseaza toate permutarile dintr-o lista cu proprietatea ca numerele
din stanga elementului maxim sunt in ordine descrescatoare, iar cele din dreapta in ordine crescatoare
ex: pt lista [1,2,5,3,7,6] o permutare valida este [2,1,7,3,5,6]
"""

"""
descriere solutie backtracking:

se da lista l, lungimea listei este len(l)


solutie candidat:
x = (x0, ..., xk), xk < len(l)
xi e {k| k e l}

conditie consistenta:
x = (x0, ..., xk), xk < len(l)
xi e {k| k e l}
oricare i, j < k ,i != j, xi != xj
daca xi = max => x0 > x1 > x2 > ... > xi < xi+1 < xi+2 < ... < xk


conditie solutie:
x = (x0, ..., xk)
consistent si k = len(l) - 1
"""

def consistent(x):
    if len(x) <= 2:
        return len(set(x)) == len(x)
    if len(set(x)) != len(x):
        return False
    maxx = max(x)
    idx = x.index(maxx)
    for i in range(idx-1):
        if x[i] < x[i + 1]:
            return False

    for i in range(idx+1, len(x) - 1):
        if x[i] > x[i + 1]:
            return False
    return True

def solutie(x, l):
    return len(x) == len(l)


def backRec(x, l):
    x.append(-1)
    for i in range(len(l)):
        x[-1] = l[i]
        if consistent(x):
            if solutie(x, l):
                print(x)
            else:
                backRec(x, l)
    x.pop()

lista = [1,2,5,3,7,6]
backRec([], lista)
