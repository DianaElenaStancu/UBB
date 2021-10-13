"""Găsiți primul număr prim mai mare decât un număr dat"""

import math

def estePrim (a):
    if a < 2:
        return 0
    if a == 2:
        return 1
    if a%2 == 0:
        return 0
    for i in range(3, int(math.sqrt(a)) + 1, 2):
        if a%i == 0:
            return 0
    return 1
    
n = int(input())
nrCerut = n + 1

while estePrim(nrCerut) == 0:
    nrCerut = nrCerut + 1

print(nrCerut)
    
