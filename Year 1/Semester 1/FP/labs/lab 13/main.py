"""14.Se dă o listă de numere întregi a1,...an. Generaţi toate permutările listei pentru care
numerele au aspect de vale (descresc până la un punct de unde cresc). valorile sunt distincte"""

#bkt
def consistent(x):
    return len(x) == len(set(x))

def solution(x, l):
    if len(x) != len(l):
        return False
    # vezi daca e secventa de vale
    i = 0
    # la inceput trb sa scada apoi sa creasca
    c =lambda: i+1 < len(x) and x[i] < len(l) and x[i + 1] < len(l)
    while c() and l[x[i]] >= l[x[i+1]] :

        i += 1
    # trec la secventa crescatoare
    if i != 0:
        i += 1

    while c() and l[x[i]] <= l[x[i+1]]:
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

def backIter(x,l, dim):
    x=[-1] #candidate solution
    while len(x)>0:
        choosed = False
        while not choosed and x[-1]<dim-1:
            x[-1] = x[-1]+1 #increase the last component
            choosed = consistent(x)
        if choosed:
            if solution(x, l):
                printSol(x, l)
            x.append(-1) # expand candidate solution
        else:
            x = x[:-1] #go back one component



#l = [10, 16, 27, 18, 14, 7]
#l = [1,1, 2, 3, 4, 4]
l = [1,2,3,4]
#
backRec([], l)
print("*********")
backIter([], l, len(l))
#print("*********")