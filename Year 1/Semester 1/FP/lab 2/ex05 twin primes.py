""" 5. Determina numerele prime p1 si p2 gemene imediat superioare numărului
 natural nenul n dat. Doua numere prime p si q sunt gemene
 daca q-p = 2."""
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
def gemene(p, q):
    if prim(p) and prim(q):
        return p, q
    if prim(q):
        return gemene(q, q + 2)
    return gemene(q + 2, q + 4)

n = int(input())
if n%2 == 0:
    print(gemene(n + 1, n + 3))
else:
    print(gemene(n + 2, n + 4))
