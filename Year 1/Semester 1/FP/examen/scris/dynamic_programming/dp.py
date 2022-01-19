"""
Pb: Ai o lista de numere. Sa se afle cea mai lunga secventa de numere pare care sunt in
ordine descrescatoare.
Ex: 52,13,16,50,15,18,21  52,50,18
"""

def longestDecreasingSublist(l):
    #lista care retine pe pozitia i lungimea maxima
    #cu proprietatea data
    lgs = [0]*len(l)
    poz = [0]*len(l)
    lgs[-1] = 1 if l[-1]%2 == 0 else -1
    poz[-1] = -1
    for i in range(len(l) - 2, -1, -1):
        lgs[i] = 1 if l[i]%2 == 0 else -1
        poz[i] = -1
        if lgs[i] == 1:
            for j in range(i + 1, len(l)):
                if l[i] >= l[j] and l[j]%2 == 0 and lgs[i] < lgs[j] + 1:
                    lgs[i] = lgs[j] + 1
                    poz[i] = j

    #caut pozitia de la care incepe sublista cu prop ceruta
    j = 0
    for i in range(len(l)):
        if lgs[i] > lgs[j]:
            j = i

    rez = []
    while j != -1:
        rez = rez + [l[j]]
        j = poz[j]

    return rez

"""
solutie:
    principiul optimalitatii:
        varianta inainte forward
    
    structura solutiei optime:
        construim doua siruri lgs, poz
            lgs[i] retine lungimea sublistei care incepe cu l[i]
            poz[i] retine indexul elementului care urmeaza dupa elementul a[i]
    
    definitia recursiva:
        lgs[n] = 1 daca l[n] par, 
               0, altfel
        poz[n] = -1
        
        lgs[k] = max{1 + lgs[i] | a[k] >= a[i] si a[i] - par, k < i < n}, a[k] - par
                -1, altfel
        
        poz[k] = arg max{1 + lgs[i] | a[k] >= a[i] si a[i] - par, k < i < n}, a[k] - par
                -1, altfel

"""



def d(l):
    lgs = [0]*len(l)
    pos = [0]*len(l)
    lgs[-1] = 1
    pos[-1] = -1
    for k in range(len(l) - 2, -1, -1):
        lgs[k] = 1
        pos[k] = -1
        for i in range(k + 1, len(l)):
            if l[k] <= l[i] and lgs[k] < lgs[i] + 1:
                pos[k] = i
                lgs[k] = lgs[i] + 1

    j = 0
    for i in range(len(l)):
        if lgs[i] > lgs[j]:
            j = i

    rez = []
    while j != -1:
        rez = rez + [l[j]]
        j = pos[j]
    return rez



l = [52,13,16,50,15,18,21]
print(longestDecreasingSublist(l))
a = [1, 2, 3, 1, 5, 3, 4, 1, 4]
print(d(a))