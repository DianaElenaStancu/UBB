"""Generați cel mai mic număr perfect mai mare decât un număr dat. Un număr este perfect daca
este egal cu suma divizorilor proprii. Ex. 6 este un număr perfect (6=1+2+3).
"""

import math
def perfect(x):
    suma = 0
    for div in range(1, math.ceil(x/2) + 1):
        if x%div == 0:
            suma = suma + div
    if suma == x:
        return 1
    return 0

n = int(input())
ans = n + 1
while perfect(ans) == 0:
    ans = ans + 1
print(ans)
