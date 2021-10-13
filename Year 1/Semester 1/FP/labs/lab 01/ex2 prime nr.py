#verificati daca un numar citit de la tastatura este prim
import math
def prim(a):
    if a < 2:
        return 0
    if a%2 == 0 and a != 2:
        return 0
    else:
        for i in range(3, math.ceil(math.sqrt(a)) + 1, 2):
            if a%i == 0:
                return 0
    return 1
            
n = int(input())
print(prim(n))
