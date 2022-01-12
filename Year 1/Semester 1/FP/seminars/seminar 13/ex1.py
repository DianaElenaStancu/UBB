"""
1) Pentru listă de monede cu valorile a1,....,an, și o valoare S. Tipăriţi toate modalităţile de a
plăti suma S cu monedele disponibile. Tipăriți un mesaj dacă suma nu se poate plăti.
"""

def printSol(x):
    for i in x:
        print(i, end= ' ')
    print()

def consistent(x, s):
    partial_sum = 0
    for el in x:
        partial_sum += el
    return partial_sum <= s

def solution(x, s):
    partial_sum = 0
    for el in x:
        partial_sum += el
    return partial_sum == s

def backRec(x, l, s):
    x.append(0)
    for i in range(len(l)):
        x[-1] = l[i]
        if consistent(x, s):
            if solution(x,s):
                printSol(x)
            else:
                backRec(x,l, s)
    x.pop()

monede = [1,2,3,4]
s = 3
backRec([], monede, s)