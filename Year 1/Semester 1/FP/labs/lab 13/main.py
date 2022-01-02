"""Se dă o listă de numere întregi a1,...an. Generaţi toate permutările listei pentru care
numerele au aspect de vale (descresc până la un punct de unde cresc)."""
#l = [10, 16, 27, 18, 14, 7]
l = [1, 2, 3, 4]

def consistent(x):
    return len(x) == len(set(x))

def solution(x, l):
    if len(x) != len(l):
        return False
    # vezi daca e secventa de vale
    i = 0
    # la inceput trb sa scada apoi sa creasca
    while i+1 < len(x) and l[x[i]] >= l[x[i+1]]:
        i += 1
    # trec la secventa crescatoare
    i += 1
    while i+1 < len(x) and l[x[i]] <= l[x[i+1]]:
        i += 1
    return i == len(l) - 1

def printSol(x,l):
    for i in x:
        print(l[i], end= ' ')
    print()

def backRec(x, l):
    x.append(0)
    for i in range(len(l)):
        x[-1] = i
        if consistent(x):
            if solution(x,l):
                printSol(x,l)
            else:
                backRec(x,l)
    x.pop()

backRec([], l)