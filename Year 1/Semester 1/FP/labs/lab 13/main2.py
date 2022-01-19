"""
Se dă o listă de numere întregi a1,...,an generați toate sub-secvențele cu proprietatea că
suma numerelor este divizibil cu N dat
"""
"""
descriere solutie bkt

fie l lista de numere a1, ..., an, 
N numar natural

solutie candidat:
x = (x0, x1, ..., xk), k < len(l)
xi apartine l

conditie solutie:
x = (x0, x1, ..., xk)
x0 + x1 + ...+ xk = s divizibila cu N

"""

def consistent(x):
    if len(set(x)) < len(x):
        return False
    for i in range(1, len(x)):
        if x[i-1] > x[i]:
            return False
    return True

def solutie(x, n):
    suma = sum(x)
    return suma % n == 0


def backRec(x, l, n):
    x.append(0)
    for i in range(len(l)):
        x[-1] = l[i]
        if consistent(x):
            if solutie(x, n):
                print(x)
            backRec(x, l, n)
    x.pop()



l = [1,2,3,4,5]
n = 2
backRec([], l, n)