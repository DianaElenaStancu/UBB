"""16. Generați cel mai mare număr perfect mai mic decât un număr dat. Daca nu exista un astfel de
număr, tipăriți un mesaj. Un număr este perfect daca este egal cu suma divizorilor proprii. Ex. 6 este
un număr perfect (6=1+2+3)."""

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
n = n - 1
if n < 6:
    print("nu exista")
else:
    while perfect(n) == 0:
        n = n - 1
    print(n)
