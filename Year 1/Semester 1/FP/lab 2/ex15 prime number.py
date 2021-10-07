"""15. Găsiți cel mai mare număr prim mai mic decât un număr dat. Daca nu exista un astfel de număr,
tipăriți un mesaj."""

import math
def prim(a):
    if a < 2:
        return 0
    if a == 2:
        return 1
    if a % 2 == 0:
        return 0
    for i in range (3, math.ceil(math.sqrt(n)) + 1, 2):
        if a%i == 0:
            return 0
    return 1

n = int(input())
n = n - 1
if n < 2:
    print("nu exista")
else:
    while prim(n) == 0 and n > 2:
        n = n - 1
    print(n)

