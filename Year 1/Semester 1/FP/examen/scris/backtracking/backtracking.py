from functools import reduce
"""def backRec(x):
    x.append(0) # adaug o noua componenta la solutia candidat
    for i in range(0, DIM):
        x[-1] = i #setex elementul curent
        if consistent(x):
            if solutie(x):
                solutionFound(x)
            backrec(x)#mergem mai departe cu urmatoarele componente
    x.pop()

def backIter(dim):
    x = [-1]
    while len(x) > 0:
        choosed = False
        while not choosed and x[-1] < dim - 1:
            x[-1] = x[-1] + 1 #cresc ultima componenta
            choosed = consistent(x, dim)
        if choosed:
            if solution(x, dim):
                solutionFound(x, dim)
            x.append(-1) #extind solutia candidat
        else:
            x = x[:-1] #sterg ultima componenenta"""

"""
descrierea solutiei backtracking
solutie candidat:
    x = (x0, x1, .., xk), k < len(cuv)
    xi e L = {l | l litera din cuvant}
    cuv  = cuvantul dat 
conditie consistenta:
    x = (x0, x1, .., xk), k < len(cuv), 
    orice i, j e {0, ..., k}, i != j => xi != xj

conditie solutie:
    x = (x0, x1, .., xk) - consistent si k = len(cuv) - 1
"""
"""#problema anagrame: se da un cuvant cu litere distincte sa se afiseze anagramele acestuia

def consistent(x):
    #in x trebuie sa fie elemente distincte
    return len(set(x)) == len(x)

def solution(x, cuv):
    return len(x) == len(cuv)

def solutionFound(x):
    anagrama = ""
    for c in x:
        anagrama = anagrama + c
    print(anagrama)

def backRec(x, cuv):
    x.append(0) #adaug un nou element solutiei candidat
    for i in range(0, len(cuv)):
        x[-1] = cuv[i] #setez ultima componenta
        if consistent(x):
            if solution(x, cuv):
                solutionFound(x)
            backRec(x, cuv)
    x.pop()

def backIter(cuv):
    scuv = [' ']
    scuv.extend(sorted(cuv))
    x = [' '] #solutia candidat
    while len(x) > 0:
        chosen = False
        while not chosen and scuv.index(x[-1]) < len(cuv):
            x[-1] = scuv[scuv.index(x[-1]) + 1] #adaug urmatoarea componenta
            chosen = consistent(x)
        if chosen:
            if solution(x, cuv):
                solutionFound(x)
            else:
                x.append(' ') #trecem la urmatorul element din solutie
        else:
            x = x[:-1] #eliminam ultima componenta


cuv = "cal"
#backRec([], cuv)
backIter(cuv)"""


#permutari vector cu elemente distincte
"""
descriere solutie backtracking 
l = lista
solutie candidat:
    x = [x0, x1, x2, ..., xk], xk < len(l)
    xi apartine {y | y apartine l}, i = {0, 1, ..., k}

conditie consistenta:
    x = [x0, x1, x2, ..., xk], xk < len(l), orice i, j e {0, ..., k}
    i != j => xi != xj

conditie solutie:
    x = [x0, x1, x2, ..., xk], xk = len(l) - 1, x - consistent
"""
"""def consistent(x):
    return len(set(x)) == len(x) #toate elementele din x sa fie distincte

def solution(x, l):
    return len(x) == len(l)


def backRec(x, l):
    x.append(0) #adaug o noua componenta
    for i in range(len(l)):
        x[-1] = l[i] #setez elementul curent
        if consistent(x):
            if solution(x, l):
                print(x)#solutionFound(x)
            backRec(x, l) #trec mai departe la urmatorul element
    x.pop() #elimin ultimul element

def backIter(l):
    x = [-1]
    y = [-1]
    y.extend(l)
    while len(x) > 0:

        chosen = False
        while not chosen and y.index(x[-1]) < len(y)-1:
            x[-1] = y[y.index(x[-1]) + 1]
            chosen = consistent(x)
        print(x)
        if chosen:
            if solution(x, l):
                print(x, "_____")
            x.append(-1)
        else:
            x = x[:-1]



l = [1,2,3] #[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]
#backRec([], l)
backIter(l)
"""

#se da o lungime n, sa se afiseze toate numerele binare cu proprietate ca
#nu exista doua cifre de 1 alaturate

"""
descriere solutiei backtracking

solutie candidat:
    x = (x0, ..., xk) k < n, xi e {0, 1}, i e {0, 1, 2, ..., k}

conditie consistenta:
    x = (x0, ..., xk) k < n, xi e {0, 1}, orice i e {0, 1, 2,.., k - 1}
    xi *x(i + 1) == 0

conditie solutie:
    x = (x0, ..., xk) k = n-1
    x - consistent 

"""

"""def consistent(x):
    if len(x) == 1:
        return True
    else:
        return not x[-1] == x[-2] == 1

def solutie(x, n):
    return len(x) == n

def solutionFound(x):
    binar = "".join(str(x))
    print(binar)



def backRec(x, n):
    x.append(0) #adaug un element solutiei candidat
    for i in range(2):
        x[-1] = i #setez elementul
        if consistent(x):
            if solutie(x, n):
                solutionFound(x)
            else:
                backRec(x, n)
    x.pop()

def backIter(n):
    x = [-1] #solutia candidat
    while len(x) > 0:
        chosen = False
        while not chosen and x[-1] < 1:
            x[-1] = x[-1] + 1
            chosen = consistent(x)
        if chosen:
            if solutie(x, n):
                print(x)
            else:
                x.append(-1)
        else:
            x = x[:-1]


n = 4
backRec([], n)
print("*********")
backIter(n)"""


"""
enunt:se da un numar natural s cu cel mult 9 cifre. afisati in ordine 
lexicografica, toate modalitatile de a-l scrie pe s ca produs de divizori proprii
distinci ai lui s

ex:
30 poate fi scris astfel:
 2 3 5
 2 15
 3 10
 5 6


descriere solutie backtracking:

solutie candidat:
    x = (x0, x1, .., xk), xi e Dn = {d | n:d, 1 < d < n}

conditie consistenta:
    x = (x0, x1, .., xk)
    xi < xi + 1, orice i e {0, 1, 2, ..., k-1}
    x0*x1*...*xk <= n

conditie solutie:
    x = (x0, x1, .., xk) - consistenta
    x0*x1*...*xk = n
"""

"""def consistent(x, n):
    produs = reduce(lambda x, y: x*y, x)
    for i in range(len(x) - 1):
        if x[i] > x[i + 1]:
            return False
    return produs <= n

def solutie(x, n):
    produs = reduce(lambda x, y: x * y, x)
    return produs == n

def backRec(x, n):
    x.append(0)
    for i in range(2, n//2+1):
        if n%i == 0:
            x[-1] = i
            if consistent(x, n):
                if solutie(x, n):
                    print(x)
                else:
                    backRec(x, n)
    x.pop()

def backIter(n):
    x = [1]
    while len(x) > 0:
        chosen = False
        while not chosen and x[-1] <= n//2:
            x[-1] = x[-1] + 1
            chosen = consistent(x, n)
        if chosen:
            if solutie(x, n):
                print(x)
            else:
                x.append(1)
        else:
            x.pop()

n = 30
#backRec([], n)
backIter(n)"""

"""
se citesc doua numere naturale n si s. 
afisati in ordine crescatoare toate numerele cu n cifre care au
suma cifrelor egala cu s si in care oricare doua cifre alaturate
au paritate diferita

descriere solutie backtracking:

solutie candidat:
x = (x0, x1, ..., xk), xk < n
xi e {0, 1, 2, 3, ..., 9}

conditie consistenta:
x = (x0, x1, ..., xk), xk < n
x0 != 0
xi e {0, 1, 2, 3, ..., 9}
xi%2 != xi+1%2
x0 + x1 + ...+ xk <= s

conditie solutie:
x = (x0, x1, ..., xk), xk = n-1 - consistent
x0 + x1 + ...+ xk = s
"""
"""def consistent(x, n, s):
    if x[0] == 0:
        return False
    sum = reduce(lambda x,y: x+y, x)
    if sum > s:
        return False
    if len(x) > n:
        return False
    if len(x) == 1:
        return True
    return x[-1]%2 != x[-2]%2

def solutie(x, n, s):
    sum = reduce(lambda x, y: x + y, x)
    return sum == s and len(x) == n

def backRec(x, n, s):
    x.append(0)
    for i in range(10):
        x[-1] = i
        if consistent(x, n, s):
            if solutie(x, n, s):
                print(x)
            else:
                backRec(x, n, s)
    x.pop()


def backIter(n, s):
    x = [-1]
    while len(x) > 0:
        chosen = False
        while not chosen and x[-1] < 10:
            x[-1] = x[-1] + 1
            chosen = consistent(x, n, s)
        if chosen:
            if solutie(x, n, s):
                print(x)
            else:
                x.append(-1)
        else:
            x.pop()

n = 4
s = 8
backIter(n, s)"""
"""
se citeste un numar natural n. afisati permutarile multimii 1, 2, 3, .., n in care
elementele pare sunt puncte fixe (se afla pe pozitii egale cu valoarea lor)

ex: n - 5
1 2 3 4 5
1 2 5 4 3
....
(2, 4) puncte fixe



descriere solutie bkt:

solutie candidat:
x = (x0, x1,..., xk) xk < n
1 <= xi <= n

conditie consistenta:
x = (x0, x1,..., xk) xk < n
1 <= xi <= n
daca xi%2 == 0 atunci xi = i
x0 != x1 != ... != xk

conditie solutie:
x = (x0, x1,..., xk) xk = n - 1, 
consistenta

"""
def consistent(x, n):
    for i in range(len(x)):
        if (i+1)%2 == 0 and i + 1 != x[i]:
            return False
    return len(x) == len(set(x))


def solutie(x, n):
    return len(x) == n

def backRec(x, n):
    x.append(0) #adaug o valoare
    for i in range(1, n + 1):
        x[-1] = i
        if consistent(x, n):
            if solutie(x, n):
                print(x)
            else:
                backRec(x, n)
    x.pop()


def backIter(n):
    x = []
    x.append(0)
    while len(x) > 0:
        chosen = False
        while not chosen and x[-1] < n:
            x[-1] = x[-1] + 1
            chosen = consistent(x, n)
        if chosen:
            if solutie(x, n):
                print(x)
            else:
                x.append(0)
        else:
            x.pop()



n = 5
#backRec([], n)
backIter(n)
