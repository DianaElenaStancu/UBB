"""14.Se dă o listă de numere întregi a1,...an. Generaţi toate permutările listei pentru care
numerele au aspect de vale (descresc până la un punct de unde cresc). valorile sunt distincte"""


def consistent(x, l):
    copy = l[:]
    for i in x:
        if i not in copy:
            return False
        else:
            copy.remove(i)
    #verificam ca descreste pana intr-un punct
    i = 0
    while i + 1 < len(x) and x[i] >= x[i+1]:
        i += 1
    #verificam ca creste pana intr-un punct
    while i + 1 < len(x) and x[i] <= x[i+1]:
        i += 1
    return  i == len(x) - 1

def solutie(x, l):
    return len(x) == len(l)

def backRec(x, l):
    x.append(0)
    for i in range(len(l)):
        x[-1] = l[i]
        if consistent(x, l):
            if solutie(x, l):
                print(x)
            else:
                backRec(x, l)
    x.pop()

def backIter(l):
    x = [-1]
    copy= l[:]
    copy.insert(0, -1)

    while len(x) > 0:
        chosen = False
        while not chosen and copy.index(x[-1]) < len(copy)-1:
            x[-1] = copy[copy.index(x[-1])+1]
            chosen = consistent(x, l)
        if chosen:
            if solutie(x, l):
                print(x)
            else:
                x.append(-1)
        else:
            x.pop()

l = [1,3,4,5]
#backRec([], l)
backIter(l)