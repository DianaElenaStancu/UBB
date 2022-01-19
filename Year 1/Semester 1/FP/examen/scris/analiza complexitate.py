def cautaZero(lista):
    if len(lista) == 0:
        return 0
    if lista[0] == 0:
        return 1
    return cautaZero(lista[1:])

l = [2,3,4,4]
print(cautaZero(l))

"""
analizati complexitatea de timp si de spatiu:

Timp:
n-general, oarecare
T(n) = 1, n = 0 sau lista[0] = 0
       1+T(n-1), altfel

    bc: primul element 0 ---> O(1)
    wc: daca nu exista 0 in lista ---> n+1 e O(n)
    ac: 

Spatiu:
T(n) = 1, n = 0 sau lista[0] = 0
       n-1+T(n-1), altfel


    bc:
    wc:
    ac:





n = 8
for i in range(n*n):
    print(i)

"""