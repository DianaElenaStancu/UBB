"""
se da o lista de nr sa se determine cel mai mare nr prim din lista
"""
import math
def isPrime(n):
    if n == 1:
        return 0
    if n == 2:
        return 1
    if n%2 == 0:
        return 0
    lim = math.floor(math.sqrt(n)) + 1
    for div in range(3, lim, 2):
        if n%div == 0:
            return 0
    return 0



def max_prime(lista):
    if(len(lista) == 1):
        if isPrime(lista[0]) == True:
            return lista[0]
        return -1
    m = len(lista)//2
    left = list[:m]
    right = list[m:]
    return max(max_prime(left), max_prime(right))