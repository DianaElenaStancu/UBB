"""Dându-se numărul natural n, determina numerele prime p1 si p2 astfel ca
 n = p1 + p2
 (verificarea ipotezei lui Goldbach). Pentru ce fel de n exista soluție?
 RASPUNS: DOAR IN CAZUL NUMERELOR PARE EXISTA ACEASTA PROPRIETATE
"""
import math

def prim(a):
    if a == 2:
        return 1
    if a % 2 == 0:
        return 0
    for i in range (3, math.ceil(math.sqrt(n)) + 1, 2):
        if a%i == 0:
            return 0
    return 1

def goldbach(p1, p2):
    print(p1, p2)
    if prim(p1) and prim(p2):
        return p1, p2
    return goldbach(p1 + 1, p2 - 1)

n = int(input())
if n%2 == 1:
    print("nu exista")
else:
    print(goldbach(2, n-2))
